//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file B1/include/DetectorHit.hh
/// \brief Definition of the B1::DetectorHit class

#ifndef B1DetectorHit_h
#define B1DetectorHit_h 1

#include <fstream>
#include <iostream>

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4VHit.hh"

class DetectorHit : public G4VHit {
public:
    explicit DetectorHit();

    ~DetectorHit() override;

    explicit DetectorHit(const DetectorHit& right);

    auto operator=(const DetectorHit& right) -> const DetectorHit&;

    auto operator==(const DetectorHit& right) const -> G4bool;

    inline auto operator new(size_t) -> void*;
    
    inline auto operator delete(void* hit) -> void;

    void Draw() override;
    
    void Print() override;
    
    void PrintToFile() const;

    void SetTrackIdentifier(const G4int &value) {
        trackIdentifier = value;        
    };
    
    void SetChamberNumber(const G4int &value) {
        chamberNumber = value;        
    };
    
    void SetDepositedEnergy(const G4double &value) {
        depositedEnergy = value;        
    };
    
    void SetPosition(const G4ThreeVector &value) {
        position = value;        
    };

    [[nodiscard]]
    auto GetTrackIdentifier() const -> G4int {
        return trackIdentifier;        
    };

    [[nodiscard]]
    auto GetChamberNumber() const -> G4int {
        return chamberNumber;        
    };
    
    [[nodiscard]]
    auto GetDepositedEnergy() const -> G4double {
        return depositedEnergy;        
    };
    
    [[nodiscard]]
    auto GetPosition() const -> G4ThreeVector {
        return position;        
    };

private:
    G4int trackIdentifier; // track identifier

    G4int chamberNumber; // chamber number

    G4double depositedEnergy; // deposited energy

    G4ThreeVector position; // spatial position
};

using DetectorHitsCollection = G4THitsCollection<DetectorHit>;
extern G4ThreadLocal G4Allocator<DetectorHit>* trackerHitAllocator;

inline auto DetectorHit::operator new(size_t) -> void*
{
    if (trackerHitAllocator == nullptr) {
        trackerHitAllocator = new G4Allocator<DetectorHit>;
    }
    return (void*) trackerHitAllocator->MallocSingle();
}

inline auto DetectorHit::operator delete(void* hit) -> void
{
    trackerHitAllocator->FreeSingle((DetectorHit*) hit);
}
#endif
