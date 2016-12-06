#include "herbshandlersimpl.h"

HerbsHandlerSimpl::HerbsHandlerSimpl(HWiface * hardware,
                                     IPolivSettingsInt * settings): hdware(hardware), stngs(settings)
{

}

void HerbsHandlerSimpl::handleHerbs()
{
    if(hdware->humidity() < stngs->getMinHumidity())
        while(hdware->humidity() < stngs->getMaxHumidity()) {
            hdware->turnPumpOn();
            delay_s(stngs->getMinPumpOnTime());
            hdware->turnPumpOff();
            delay_s(stngs->getWaitTimeAfterpump());
        }
}


void HerbsHandlerSimpl::setMode(PolivMode)
{
    // TODO
}

PolivMode HerbsHandlerSimpl::getPolivMode()
{
    // TODO
}

PolivStage HerbsHandlerSimpl::getStatus()
{
    // TODO
}
