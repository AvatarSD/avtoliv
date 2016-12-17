#include "herbshandlersimpl.h"

HerbsHandlerSimpl::HerbsHandlerSimpl(HWiface * hardware,
                                     ISettingsInt * settings): hardware(hardware), settings(settings)
{
    this->status = DeviceStatus::WaitForMinHumidity;

    DeviceMode mode = settings->getDeviceMode();
    if(mode == DeviceMode::ManualOn)
        hardware->turnPumpOn();
    else
        hardware->turnPumpOff();
}

void HerbsHandlerSimpl::handleHerbs()
{
    if(settings->getDeviceMode() == DeviceMode::Auto)
        if(hardware->humidity() < settings->getMinHumidity())
            while(hardware->humidity() < settings->getMaxHumidity()) {
                hardware->turnPumpOn();
                this->status = DeviceStatus::PumpOn;
                delay_s(settings->getPumpOnTime());
                hardware->turnPumpOff();
                this->status = DeviceStatus::AfterPumpWait;
                delay_s(settings->getAbsorbedTime());
            }
    this->status = DeviceStatus::WaitForMinHumidity;
}

void HerbsHandlerSimpl::setDeviceMode(DeviceMode mode)
{
    settings->setDeviceMode(mode);
    if(mode == DeviceMode::ManualOn)
        hardware->turnPumpOn();
    else
        hardware->turnPumpOff();
}

DeviceMode HerbsHandlerSimpl::getDeviceMode() const
{
    return settings->getDeviceMode();
}
DeviceStatus HerbsHandlerSimpl::getDeviceStatus() const
{
    return this->status;
}
HumidityVal HerbsHandlerSimpl::getHumidity()
{
    return hardware->humidity();
}
