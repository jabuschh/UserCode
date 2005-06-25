// -*- C++ -*-
//
// Package:    WhatsItESProducer
// Class:      WhatsItESProducer
// 
/**\class WhatsItESProducer WhatsItESProducer.h test/WhatsItESProducer/interface/WhatsItESProducer.h

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Chris Jones
//         Created:  Fri Jun 24 14:33:04 EDT 2005
// $Id$
//
//


// system include files
#include <memory>
#include "boost/shared_ptr.hpp"

// user include files
#include "FWCore/CoreFramework/interface/ModuleFactory.h"
#include "FWCore/CoreFramework/interface/ESProducer.h"
#include "FWCore/CoreFramework/interface/ESHandle.h"

#include "FWCore/FWCoreIntegration/src/WhatsIt.h"
#include "FWCore/FWCoreIntegration/src/Doodad.h"
#include "FWCore/FWCoreIntegration/src/GadgetRcd.h"


//
// class decleration
//
namespace edmreftest {

class WhatsItESProducer : public edm::eventsetup::ESProducer {
   public:
      WhatsItESProducer( const edm::ParameterSet& );
      ~WhatsItESProducer();

      typedef std::auto_ptr<WhatsIt> ReturnType;

      ReturnType produce( const GadgetRcd & );
   private:
      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
WhatsItESProducer::WhatsItESProducer( const edm::ParameterSet& iConfig )
{
   //the following line is needed to tell the framework what
   // data is being produced
   setWhatProduced(this);

   //now do what ever other initialization is needed
}


WhatsItESProducer::~WhatsItESProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
WhatsItESProducer::ReturnType
WhatsItESProducer::produce( const GadgetRcd& iRecord )
{
   using namespace edm::eventsetup;
   using namespace edmreftest;

   ESHandle<Doodad> doodad;
   iRecord.get( doodad );
   
   std::auto_ptr<WhatsIt> pWhatsIt( new WhatsIt ) ;

   pWhatsIt->a = doodad->a;

   return pWhatsIt ;
}
}

using namespace edmreftest;
//define this as a plug-in
DEFINE_FWK_EVENTSETUP_MODULE(WhatsItESProducer)
