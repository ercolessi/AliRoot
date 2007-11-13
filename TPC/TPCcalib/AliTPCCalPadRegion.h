#ifndef ALITPCCALPADREGION_H
#define ALITPCCALPADREGION_H

/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

#include <TNamed.h>
#include <TString.h>
#include <TObjArray.h>
#include <TIterator.h>

class AliTPCCalPadRegion: public TNamed {
public:
   AliTPCCalPadRegion();
   AliTPCCalPadRegion(const AliTPCCalPadRegion& obj);
   AliTPCCalPadRegion(const char *name, const char *title);
   AliTPCCalPadRegion(const TString &name, const TString &title) : TNamed(name, title) { AliTPCCalPadRegion(name.Data(), title.Data()); }
   virtual ~AliTPCCalPadRegion() { delete fObjects; }
   AliTPCCalPadRegion& operator=(const AliTPCCalPadRegion& obj);
   
   virtual TObject*   GetObject(UInt_t segment, UInt_t padType)
      { return BoundsOk("GetObject", segment, padType) ? fObjects->At(segment+fgkNSegments*padType) : 0x0; }
   virtual void       SetObject(TObject* obj, UInt_t segment, UInt_t padType)
      { if (BoundsOk("SetObject", segment, padType)) fObjects->AddAt(obj, segment+fgkNSegments*padType); }
   virtual void       Delete(Option_t* option = "") { if (fObjects) fObjects->Delete(); }
   virtual TIterator* MakeIterator(Bool_t direction = kIterForward) const { return fObjects->MakeIterator(direction); }
   static  UInt_t     GetNSegments() { return fgkNSegments; }
   static  UInt_t     GetNPadTypes() { return fgkNPadTypes; }
   void       GetPadRegionCenterLocal(UInt_t padType, Double_t* xy);
    
protected:
   virtual Bool_t BoundsOk(const char* where, UInt_t segment, UInt_t padType) const
      { return (segment >= fgkNSegments || padType >= fgkNPadTypes) ? OutOfBoundsError(where, segment, padType) : kTRUE; }
   virtual Bool_t OutOfBoundsError(const char* where, UInt_t segment, UInt_t padType) const
      { Error(where, "Index out of bounds (trying to access segment %d, pad type %d).", segment, padType); return kFALSE; }

   TObjArray* fObjects;     // array containing an object for each pad region

   static const UInt_t fgkNSegments = 36;    // number of TPC sectors, 0-17: A side, 18-35: C side (IROC and OROC are treated as one sector)
   static const UInt_t fgkNPadTypes = 3;     // number of pad types, 0: short pads, 1: medium pads, 2: long pads

   ClassDef(AliTPCCalPadRegion, 1)
};


#endif
