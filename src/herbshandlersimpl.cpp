#include "herbshandlersimpl.h"

HerbsHandlerSimpl::HerbsHandlerSimpl(HWiface * hardware,
                                     IPolivSettingsInt * settings): hdware(hardware), stngs(settings)
{
    this->stage = DeviceStatus::WaitForMinHumidity;

    DeviceMode mode = stngs->getMode();
    if(mode == DeviceMode::ManualOn)
        hdware->turnPumpOn();
    else
        hdware->turnPumpOff();
}

void HerbsHandlerSimpl::handleHerbs()
{
    if(stngs->getMode() == DeviceMode::Auto)
        if(hdware->humidity() < stngs->getMinHumidity())
            while(hdware->humidity() < stngs->getMaxHumidity()) {
                hdware->turnPumpOn();
                this->stage = DeviceStatus::PumpOn;
                delay_s(stngs->getMinPumpOnTime());
                hdware->turnPumpOff();
                this->stage = DeviceStatus::AfterPumpWait;
                delay_s(stngs->getWaitTimeAfterpump());
            }
    this->stage = DeviceStatus::WaitForMinHumidity;
}


void HerbsHandlerSimpl::setMode(DeviceMode mode)
{
    stngs->setMode(mode);
    if(mode == DeviceMode::ManualOn)
        hdware->turnPumpOn();
    else
        hdware->turnPumpOff();
}

DeviceMode HerbsHandlerSimpl::getPolivMode()
{
    return stngs->getMode();
}

DeviceStatus HerbsHandlerSimpl::getStatus()
{
    return this->stage;
}


uint16_t HerbsHandlerSimpl::getHumidity(uint8_t)
{
    return hdware->humidity();
}
