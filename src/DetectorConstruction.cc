
#include "DetectorConstruction.hh"



namespace med_linac
{

    DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {
        fLinacHeadPos = new G4ThreeVector();
        fLinacHeadRot = new G4RotationMatrix();
        fGunAnchorPos = new G4ThreeVector();
    }
	

    void DetectorConstruction::SetLinacHeadAngle(G4ThreeVector phiThetaPsi) {
        fLinacHeadRot->setPhi(phiThetaPsi.getX());
        fLinacHeadRot->setTheta(phiThetaPsi.getY());
        fLinacHeadRot->setPsi(phiThetaPsi.getZ());
        
        MoveLinacHead();
    }


    void DetectorConstruction::SetLinacHeadPosition(G4ThreeVector xyz) {
        *fLinacHeadPos = xyz;

        MoveLinacHead();

    }

    void DetectorConstruction::ShiftLinacHeadPosition(G4ThreeVector xyz) {
        *fLinacHeadPos += xyz;

        MoveLinacHead();
    }

    void DetectorConstruction::ShiftLinacHeadRotation(G4ThreeVector phiThetaPsi) {
        fLinacHeadRot->setPhi(fLinacHeadRot->getPhi() + phiThetaPsi.getX());
        fLinacHeadRot->setTheta(fLinacHeadRot->getTheta() + phiThetaPsi.getY());
        fLinacHeadRot->setPsi(fLinacHeadRot->getPsi() + phiThetaPsi.getZ());

        G4cout << *fLinacHeadRot << G4endl;

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