#include "G4Event.hh"
//#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "Randomize.hh"
#include "CLHEP/Random/Random.h"
#include "gesimPrimaryGeneratorAction.hh"

#include "G4HEPEvtInterface.hh"
#include "gesimDetectorConstruction.hh"
#include "G4Tubs.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4HEPEvtInterface.hh"
#include "G4SystemOfUnits.hh"
#include "G4Neutron.hh"
#include "G4Gamma.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
G4VPrimaryGenerator* HEPEvt;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

gesimPrimaryGeneratorAction::gesimPrimaryGeneratorAction(gesimDetectorConstruction* gesimDC):gesimDetector(gesimDC),fParticleGun(0)
{
    G4int nofParticles = 1;
    //fParticleGun = new G4ParticleGun(nofParticles);
    HEPEvt = new G4HEPEvtInterface("/home/amslivar/work/AmBe_v2/AmBe_GeSim_efficiency/am241events.data");

    G4cout << "Opened generator data file " << G4endl;
    //fPrimaryGenerator = new B4PrimaryGenerator(gesimDC);
    
}

gesimPrimaryGeneratorAction::~gesimPrimaryGeneratorAction()
{
    //delete fParticleGun;
    delete HEPEvt;
    //delete fPrimaryGenerator;
}

void gesimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

   G4ParticleDefinition *gammaParticle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
   //G4ParticleDefinition *alphaParticle = G4Alpha::AlphaDefinition();
   //G4ParticleDefinition *neutron = G4Neutron::Definition();
   //const G4long * table_entry = CLHEP::HepRandom::getTheSeeds();
   //G4cout << "PGA: Random Seed: " << *table_entry << ", " << *(table_entry+1) << G4endl;
   //G4cout << "PGA: Random Seed Index: " << CLHEP::HepRandom::getTheSeed() << G4endl;
   //fParticleGun->GeneratePrimaryVertex(anEvent);
/*
    auto outerCapPV  = gesimDetector->GetOuterCapsulePV();
    auto ssShieldPV  = gesimDetector->GetSSShieldPV();
    auto outCapLV = outerCapPV->GetLogicalVolume();
    auto ssShieldLV = ssShieldPV->GetLogicalVolume();
    auto outCapS = outCapLV->GetSolid();
    auto ssShieldS = ssShieldLV->GetSolid();
    auto outerCapTranslation = outerCapPV->GetObjectTranslation();
    auto ssShieldTranslation = ssShieldPV->GetObjectTranslation();
    //G4cout << "outer capsule Translation :" << outerCapTranslation.getX() << "\t" <<  outerCapTranslation.getY() << "\t" << outerCapTranslation.getZ() << G4endl;

    auto middleCapPV  = gesimDetector->GetMiddleCapsulePV();
    auto wShieldPV  = gesimDetector->GetWShieldPV();
    auto middleCapTranslation = middleCapPV->GetObjectTranslation();
    auto wShieldTranslation = wShieldPV->GetObjectTranslation();
    //G4cout << "middle capsule Translation :" << middleCapTranslation.getX() << "\t" <<  middleCapTranslation.getY() << "\t" << middleCapTranslation.getZ() << G4endl;


    auto sourcePV  = gesimDetector->GetSourcePV();
    auto srcCorePV  = gesimDetector->GetSrcCorePV();
    auto sourceTranslation = sourcePV->GetObjectTranslation();
    auto srcTranslation = srcCorePV->GetObjectTranslation();
    //G4cout << "source Translation :" << sourceTranslation.getX() << "\t" <<  sourceTranslation.getY() << "\t" << sourceTranslation.getZ() << G4endl;
    auto sourceLV = sourcePV->GetLogicalVolume();
    auto sourceS = sourceLV->GetSolid();
	
    auto srcCtrInCvtyCord = G4ThreeVector(outerCapTranslation.getX() - middleCapTranslation.getZ() - sourceTranslation.getZ(), outerCapTranslation.getY(), outerCapTranslation.getZ()); //remember the capsule is in rotated position so x_cavity<->z_source
*/    
    auto srcCtrInCvtyCord =  G4ThreeVector(0.12*CLHEP::mm, 0.*CLHEP::mm, -4.*CLHEP::mm);//In my implementation the sielding and the source core of the AmBe is concentric so.. didn't have to go through all the steps I did in case of AmLi. 
    //auto srcCtrInCvtyCord =  G4ThreeVector(-8.875*CLHEP::mm, 0.*CLHEP::mm, 0.*CLHEP::mm);//In my imolementation the sielding and the source core of the AmBe is concentric so.. didn't have to go through all the steps I did in case of AmLi. 
/*
    G4cout << "src center in cavity coordinate : " << G4endl;
    G4cout << "X coord: " << srcCtrInCvtyCord.getX() << G4endl;
    G4cout << "Y coord: " << srcCtrInCvtyCord.getY() << G4endl;
    G4cout << "Z coord: " << srcCtrInCvtyCord.getZ() << G4endl;
*/  

    CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine);
    CLHEP::HepRandom::setTheSeed((unsigned)clock());
    //vector<double> rndVec;
    //CLHEP::HepRandomVector::flatArray(new CLHEP::MTwistEngine,2,rndVec);
/*    auto rSource = 2.0*CLHEP::mm;  //sourceS->GetOuterRadius();
    auto hSource = 4.0*CLHEP::mm; //sourceS->GetZHalfLength();
    auto rSourceRnd = rSource*G4UniformRand();
    auto alpha = CLHEP::twopi*G4UniformRand();    //remember the capsule is in rotated position so x_cavity<->z_source
    auto yRnd = rSourceRnd*std::cos(alpha);
    auto zRnd = rSourceRnd*std::sin(alpha);
    auto xRnd = hSource*(2*G4UniformRand()-1);
    

    G4ThreeVector position(srcCtrInCvtyCord.getX()+xRnd, srcCtrInCvtyCord.getY()+yRnd, srcCtrInCvtyCord.getZ()+zRnd);
    //position1 = srcCtrInCvtyCord
    //G4ThreeVector position1 = outCapS->GetPointOnSurface();
    //G4ThreeVector position;
    //position.setX(position1.getX()+outerCapTranslation.getX());
    //position.setY(position1.getY()+outerCapTranslation.getY());
    //position.setZ(position1.getZ()+outerCapTranslation.getZ());*/
    HEPEvt->SetParticlePosition(srcCtrInCvtyCord);
    //HEPEvt->SetParticlePosition(position);
    HEPEvt->GeneratePrimaryVertex(anEvent);
    //fParticleGun->SetParticleDefinition(gammaParticle);
    //fParticleGun->SetParticleDefinition(neutron);
    //fParticleGun->SetParticlePosition(srcCtrInCvtyCord);
    //fParticleGun->SetParticlePosition(position);
    //fParticleGun->SetParticlePosition(srcCtrInCvtyCord);
    auto alpha = CLHEP::twopi*G4UniformRand();
    float dirZ = -1.0 + 2*G4UniformRand();
    auto dirR = sqrt(1.-dirZ*dirZ);
    auto dirX = dirR*std::cos(alpha);
    auto dirY = dirR*std::sin(alpha); 
    //auto nEnergy = 3.*G4UniformRand();
    //float aEnergy = 4438.0; 
    //fParticleGun->SetParticleEnergy(aEnergy*keV);
    //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(dirX,dirY,dirZ));
    //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1,0,0));
    //fParticleGun->GeneratePrimaryVertex(anEvent);
    //fPrimaryGenerator->GeneratePrimaryVertex(anEvent);
}



