
#include "DetectorConstruction.hh"


#include "G4VisAttributes.hh"

#include "LinacHeadSingleton.hh"

namespace med_linac
{

    DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {
        fLinacHeadPos = new G4ThreeVector();
        fLinacHeadRot = new G4RotationMatrix();
        fGunAnchorPos = new G4ThreeVector();

        fLinacHeadPhi = new G4double();
        fLinacHeadTheta = new G4double();
        fLinacHeadPsi = new G4double();
    }
	

    void DetectorConstruction::SetLinacHeadAngle(G4ThreeVector phiThetaPsi) {
        fLinacHeadRot->setPhi(-phiThetaPsi.getX());
        fLinacHeadRot->setTheta(-phiThetaPsi.getY());
        fLinacHeadRot->setPsi(-phiThetaPsi.getZ());

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
        *fLinacHeadPos += xyz;
        MoveLinacHead();
    }


    void DetectorConstruction::ShiftLinacHeadRotation(G4ThreeVector phiThetaPsi) {
        *fLinacHeadPhi += phiThetaPsi.getX();
        *fLinacHeadTheta += phiThetaPsi.getY();
        *fLinacHeadPsi += phiThetaPsi.getZ();

        fLinacHeadRot->setPhi(-*fLinacHeadPhi);
        fLinacHeadRot->setTheta(-*fLinacHeadTheta);
        fLinacHeadRot->setPsi(-*fLinacHeadPsi);

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

        // NOTE: THIS IS FOR DET_CONST.CC
        // Create a half hollow lead semi-sphere around the backside
        /*
        G4Material* lead = nist->FindOrBuildMaterial("G4_Pb");
        G4RotationMatrix* protectorRotation = new G4RotationMatrix();
        protectorRotation->rotateX(270. * deg);

        G4double protectorThickness = 6 * cm;

        G4Sphere* solidProtector = new G4Sphere(
            "solidProtector",
            linacHeadThicknessXY - protectorThickness,
            linacHeadThicknessXY,
            0 * deg,
            180 * deg,
            0 * deg,
            180 * deg
        );

        G4LogicalVolume* logProtector = new G4LogicalVolume(
            solidProtector,
            lead,
            "logProtector"
        );

        new G4PVPlacement(
            protectorRotation,
            G4ThreeVector(),
            logProtector,
            "solidProtector",
            logicHead,
            false,
            0
        );
        */


    }


    void DetectorConstruction::ConstructSDandField() {

        /*

        // Add our PhantomSD to the phantom

        // Assign names
        G4String phantomSDName = "phantomSD";
        G4String phantomHCName = "phantomHC";

        // Create our SD
        auto phantomSD = new PhantomSD(phantomSDName, phantomHCName);

        // add the SD to the singleton
        G4SDManager::GetSDMpointer()->AddNewDetector(phantomSD);

        // assign the sd to the volume we want
        SetSensitiveDetector("logicPhantom", phantomSD);

        */
    }

}