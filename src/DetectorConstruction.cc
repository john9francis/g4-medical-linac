
#include "DetectorConstruction.hh"



namespace med_linac
{
	

    void DetectorConstruction::SetLinacHeadAngle(G4ThreeVector phiThetaPsi) {
        // we're going to get the linac head and rotate it based on that angle. 
        G4RotationMatrix* newRot = new G4RotationMatrix(phiThetaPsi.getX(), phiThetaPsi.getY(), phiThetaPsi.getZ());
        
        fLinacHead->SetRotation(newRot);
    }


    void DetectorConstruction::SetLinacHeadPosition(G4ThreeVector xyz) {
        //fLinacHead->SetTranslation(xyz);
        G4RotationMatrix linacHeadRot = fLinacHead->GetObjectRotationValue();
        MoveLinacHead(xyz, linacHeadRot);

    }

    void DetectorConstruction::MoveLinacHead(G4ThreeVector xyz, G4RotationMatrix& rotMatrix) {
        // To move the Linac Head we need to create a new physical volume of it, then delete the old one.
        // The reason for this is because the functions SetRotation and SetTranslation seem to be broken.

        // Step one: get all the parameters we need
        G4RotationMatrix* newRot = new G4RotationMatrix();
        *newRot = rotMatrix;
        auto logicHead = fLinacHead->GetLogicalVolume();
        auto name = fLinacHead->GetName();
        auto logicMother = fLinacHead->GetMotherLogical();

        // next, delete the old linac head and create the new one.
        delete fLinacHead;
        
        fLinacHead = new G4PVPlacement(
            newRot,
            xyz,
            logicHead,
            name,
            logicMother,
            false,
            0);

    }

}