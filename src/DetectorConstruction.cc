
#include "DetectorConstruction.hh"



namespace med_linac
{

    DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {
        // initialize variables in heap memory
        fLinacHeadPos = new G4ThreeVector();
        fLinacHeadRot = new G4RotationMatrix();
        fGunAnchorPos = new G4ThreeVector();

        fLinacHeadPhi = new G4double();
        fLinacHeadTheta = new G4double();
        fLinacHeadPsi = new G4double();

        fPurePhotonBeamFlag = new G4bool(false);
    }

    void DetectorConstruction::SetPurePhotonBeamFlag(G4bool newBool) {
        *fPurePhotonBeamFlag = newBool;
    }


    void DetectorConstruction::AddFlatteningFilter() {
        // Adds a flattening filter where it's supposed to go

        if (fFlatteningFilter) {
            G4cout
                << "Can't add flattening filter,"
                << " it already exists."
                << G4endl;
            return;
        }

        auto nist = G4NistManager::Instance();
        G4Material* tungsten = nist->FindOrBuildMaterial("G4_W");



        // Create flattening filter
        G4double coneInnerRadius = 0.0;
        G4double coneOuterRadius = 4.0 * cm;
        G4double coneHeight = .8 * cm;
        G4double startPhi = 0.0;
        G4double endPhi = 360.0 * deg;

        G4double ffZ = 8 * cm;
        G4ThreeVector ffPos = G4ThreeVector(0, 0, ffZ);
        G4Cons* solidFF = new G4Cons("solidFF", 0, 0, 0, coneOuterRadius, coneHeight, startPhi, endPhi);
        G4LogicalVolume* logicFF = new G4LogicalVolume(solidFF, tungsten, "logicFF");

        // get logic head from phys head
        G4LogicalVolume* logicHead = fLinacHead->GetLogicalVolume();

        fFlatteningFilter = new G4PVPlacement(
            nullptr,
            ffPos,
            logicFF,
            "physFF",
            logicHead,
            false,
            0);
    }

    void DetectorConstruction::RemoveFlatteningFilter() {
        // Removes the flattening filter from the linac head

        if (fFlatteningFilter) {
            delete fFlatteningFilter;
            fFlatteningFilter = nullptr;
        }
        else {
            G4cout
                << "Can't remove flattening filter,"
                << " it currently does not exist. "
                << G4endl;
        }
    }


    void DetectorConstruction::SetLinacHeadAngle(G4ThreeVector phiThetaPsi) {

        // set the linac head rotation matrix
        // note the negative values because this rotation matrix is not for the 
        // linac head itsself, rather for the world's frame of reference
        // (I know, it's weird)
        //
        fLinacHeadRot->setPhi(-phiThetaPsi.getX());
        fLinacHeadRot->setTheta(-phiThetaPsi.getY());
        fLinacHeadRot->setPsi(-phiThetaPsi.getZ());

        // Set the phi theta and psi variables so we can use them later
        *fLinacHeadPhi = phiThetaPsi.getX();
        *fLinacHeadTheta = phiThetaPsi.getY();
        *fLinacHeadPsi = phiThetaPsi.getZ();


        MoveLinacHead();
    }


    void DetectorConstruction::SetLinacHeadPosition(G4ThreeVector xyz) {
        *fLinacHeadPos = xyz;

        MoveLinacHead();

    }

    void DetectorConstruction::ShiftLinacHeadPosition(G4ThreeVector xyz) {
        // note the += instead of the =
        *fLinacHeadPos += xyz;

        MoveLinacHead();
    }

    void DetectorConstruction::ShiftLinacHeadRotation(G4ThreeVector phiThetaPsi) {
        // Add on the shifted angle
        *fLinacHeadPhi += phiThetaPsi.getX();
        *fLinacHeadTheta += phiThetaPsi.getY();
        *fLinacHeadPsi += phiThetaPsi.getZ();

        fLinacHeadRot->setPhi(-*fLinacHeadPhi);
        fLinacHeadRot->setTheta(-*fLinacHeadTheta);
        fLinacHeadRot->setPsi(-*fLinacHeadPsi);

        MoveLinacHead();
    }

    void DetectorConstruction::MoveToAim() {
        // shifts the x y and z coordinates to aim at the phantom
        // based on the theta value. NOTE: doesn't work well with 
        // phi and psi, which are buggy anyway.
        //
        G4double radius = fLinacHeadPos->mag();
        G4double x = fLinacHeadPos->getX();
        G4double y = - radius * sin(*fLinacHeadTheta);
        G4double z = - radius * cos(*fLinacHeadTheta);

        *fLinacHeadPos = G4ThreeVector(x, y, z);

        MoveLinacHead();
    }

    void DetectorConstruction::MoveLinacHead() {
        // To move the Linac Head we need to create a new physical volume of it, then delete the old one.
        // The reason for this is because the functions SetRotation and SetTranslation seem to be broken.

        // Step one: get all the parameters we need
        auto logicHead = fLinacHead->GetLogicalVolume();
        auto name = fLinacHead->GetName();
        auto logicMother = fLinacHead->GetMotherLogical();

        // next, delete the old linac head and create the new one.
        delete fLinacHead;

        fLinacHead = new G4PVPlacement(
            fLinacHeadRot,
            *fLinacHeadPos,
            logicHead,
            name,
            logicMother,
            false,
            0);

    }

}