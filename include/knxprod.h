#pragma once


#define paramDelay(time) (uint32_t)( \
            (time & 0xC000) == 0xC000 ? (time & 0x3FFF) * 100 : \
            (time & 0xC000) == 0x0000 ? (time & 0x3FFF) * 1000 : \
            (time & 0xC000) == 0x4000 ? (time & 0x3FFF) * 60000 : \
            (time & 0xC000) == 0x8000 ? ((time & 0x3FFF) > 1000 ? 3600000 : \
                                         (time & 0x3FFF) * 3600000 ) : 0 )
                                             
#define MAIN_OpenKnxId 0xA6
#define MAIN_ApplicationNumber 3
#define MAIN_ApplicationVersion 5
#define MAIN_ParameterSize 14329
#define MAIN_MaxKoNumber 1049
#define MAIN_OrderNumber "OpenKnxTouchRound"
#define BASE_ModuleVersion 19
#define UCT_ModuleVersion 2
#define BRI_ModuleVersion 1
#define TCH_ModuleVersion 1
#define LOG_ModuleVersion 53
#define FCB_ModuleVersion 4
#define BTN_ModuleVersion 5
// Parameter with single occurrence


#define BASE_StartupDelayBase                     0      // 2 Bits, Bit 7-6
#define     BASE_StartupDelayBaseMask 0xC0
#define     BASE_StartupDelayBaseShift 6
#define BASE_StartupDelayTime                     0      // 14 Bits, Bit 13-0
#define     BASE_StartupDelayTimeMask 0x3FFF
#define     BASE_StartupDelayTimeShift 0
#define BASE_HeartbeatDelayBase                   2      // 2 Bits, Bit 7-6
#define     BASE_HeartbeatDelayBaseMask 0xC0
#define     BASE_HeartbeatDelayBaseShift 6
#define BASE_HeartbeatDelayTime                   2      // 14 Bits, Bit 13-0
#define     BASE_HeartbeatDelayTimeMask 0x3FFF
#define     BASE_HeartbeatDelayTimeShift 0
#define BASE_Timezone                             4      // 5 Bits, Bit 7-3
#define     BASE_TimezoneMask 0xF8
#define     BASE_TimezoneShift 3
#define BASE_TimezoneSign                         4      // 1 Bit, Bit 7
#define     BASE_TimezoneSignMask 0x80
#define     BASE_TimezoneSignShift 7
#define BASE_TimezoneValue                        4      // 4 Bits, Bit 6-3
#define     BASE_TimezoneValueMask 0x78
#define     BASE_TimezoneValueShift 3
#define BASE_CombinedTimeDate                     4      // 1 Bit, Bit 2
#define     BASE_CombinedTimeDateMask 0x04
#define     BASE_CombinedTimeDateShift 2
#define BASE_SummertimeAll                        4      // 2 Bits, Bit 1-0
#define     BASE_SummertimeAllMask 0x03
#define     BASE_SummertimeAllShift 0
#define BASE_SummertimeDE                         4      // 2 Bits, Bit 1-0
#define     BASE_SummertimeDEMask 0x03
#define     BASE_SummertimeDEShift 0
#define BASE_SummertimeWorld                      4      // 2 Bits, Bit 1-0
#define     BASE_SummertimeWorldMask 0x03
#define     BASE_SummertimeWorldShift 0
#define BASE_SummertimeKO                         4      // 2 Bits, Bit 1-0
#define     BASE_SummertimeKOMask 0x03
#define     BASE_SummertimeKOShift 0
#define BASE_Latitude                             5      // float
#define BASE_Longitude                            9      // float
#define BASE_Diagnose                            14      // 1 Bit, Bit 7
#define     BASE_DiagnoseMask 0x80
#define     BASE_DiagnoseShift 7
#define BASE_Watchdog                            14      // 1 Bit, Bit 6
#define     BASE_WatchdogMask 0x40
#define     BASE_WatchdogShift 6
#define BASE_ReadTimeDate                        14      // 1 Bit, Bit 5
#define     BASE_ReadTimeDateMask 0x20
#define     BASE_ReadTimeDateShift 5
#define BASE_HeartbeatExtended                   14      // 1 Bit, Bit 4
#define     BASE_HeartbeatExtendedMask 0x10
#define     BASE_HeartbeatExtendedShift 4
#define BASE_InternalTime                        14      // 1 Bit, Bit 3
#define     BASE_InternalTimeMask 0x08
#define     BASE_InternalTimeShift 3
#define BASE_ManualSave                          14      // 3 Bits, Bit 2-0
#define     BASE_ManualSaveMask 0x07
#define     BASE_ManualSaveShift 0
#define BASE_PeriodicSave                        15      // 8 Bits, Bit 7-0
#define BASE_Dummy                               45      // uint8_t

// Zeitbasis
#define ParamBASE_StartupDelayBase                    ((knx.paramByte(BASE_StartupDelayBase) & BASE_StartupDelayBaseMask) >> BASE_StartupDelayBaseShift)
// Zeit
#define ParamBASE_StartupDelayTime                    (knx.paramWord(BASE_StartupDelayTime) & BASE_StartupDelayTimeMask)
// Zeit (in Millisekunden)
#define ParamBASE_StartupDelayTimeMS                  (paramDelay(knx.paramWord(BASE_StartupDelayTime)))
// Zeitbasis
#define ParamBASE_HeartbeatDelayBase                  ((knx.paramByte(BASE_HeartbeatDelayBase) & BASE_HeartbeatDelayBaseMask) >> BASE_HeartbeatDelayBaseShift)
// Zeit
#define ParamBASE_HeartbeatDelayTime                  (knx.paramWord(BASE_HeartbeatDelayTime) & BASE_HeartbeatDelayTimeMask)
// Zeit (in Millisekunden)
#define ParamBASE_HeartbeatDelayTimeMS                (paramDelay(knx.paramWord(BASE_HeartbeatDelayTime)))
// Zeitzone
#define ParamBASE_Timezone                            ((knx.paramByte(BASE_Timezone) & BASE_TimezoneMask) >> BASE_TimezoneShift)
// Zeitzone-Vorzeichen
#define ParamBASE_TimezoneSign                        ((bool)(knx.paramByte(BASE_TimezoneSign) & BASE_TimezoneSignMask))
// Zeitzone-Wert
#define ParamBASE_TimezoneValue                       ((knx.paramByte(BASE_TimezoneValue) & BASE_TimezoneValueMask) >> BASE_TimezoneValueShift)
// Empfangen über
#define ParamBASE_CombinedTimeDate                    ((bool)(knx.paramByte(BASE_CombinedTimeDate) & BASE_CombinedTimeDateMask))
// Sommerzeit ermitteln durch
#define ParamBASE_SummertimeAll                       (knx.paramByte(BASE_SummertimeAll) & BASE_SummertimeAllMask)
// Sommerzeit ermitteln durch
#define ParamBASE_SummertimeDE                        (knx.paramByte(BASE_SummertimeDE) & BASE_SummertimeDEMask)
// Sommerzeit ermitteln durch
#define ParamBASE_SummertimeWorld                     (knx.paramByte(BASE_SummertimeWorld) & BASE_SummertimeWorldMask)
// Sommerzeit ermitteln durch
#define ParamBASE_SummertimeKO                        (knx.paramByte(BASE_SummertimeKO) & BASE_SummertimeKOMask)
// Breitengrad
#define ParamBASE_Latitude                            (knx.paramFloat(BASE_Latitude, Float_Enc_IEEE754Single))
// Längengrad
#define ParamBASE_Longitude                           (knx.paramFloat(BASE_Longitude, Float_Enc_IEEE754Single))
// Diagnoseobjekt anzeigen
#define ParamBASE_Diagnose                            ((bool)(knx.paramByte(BASE_Diagnose) & BASE_DiagnoseMask))
// Watchdog aktivieren
#define ParamBASE_Watchdog                            ((bool)(knx.paramByte(BASE_Watchdog) & BASE_WatchdogMask))
// Bei Neustart vom Bus lesen
#define ParamBASE_ReadTimeDate                        ((bool)(knx.paramByte(BASE_ReadTimeDate) & BASE_ReadTimeDateMask))
// Erweitertes "In Betrieb"
#define ParamBASE_HeartbeatExtended                   ((bool)(knx.paramByte(BASE_HeartbeatExtended) & BASE_HeartbeatExtendedMask))
// InternalTime
#define ParamBASE_InternalTime                        ((bool)(knx.paramByte(BASE_InternalTime) & BASE_InternalTimeMask))
// Manuelles speichern
#define ParamBASE_ManualSave                          (knx.paramByte(BASE_ManualSave) & BASE_ManualSaveMask)
// Zyklisches speichern
#define ParamBASE_PeriodicSave                        (knx.paramByte(BASE_PeriodicSave))
// 
#define ParamBASE_Dummy                               (knx.paramByte(BASE_Dummy))

#define BASE_KoHeartbeat 1
#define BASE_KoTime 2
#define BASE_KoDate 3
#define BASE_KoDiagnose 7
#define BASE_KoIsSummertime 10
#define BASE_KoManualSave 11
#define BASE_KoDateTime 12

// In Betrieb
#define KoBASE_Heartbeat                           (knx.getGroupObject(BASE_KoHeartbeat))
// Uhrzeit/Datum
#define KoBASE_Time                                (knx.getGroupObject(BASE_KoTime))
// Datum
#define KoBASE_Date                                (knx.getGroupObject(BASE_KoDate))
// Diagnose
#define KoBASE_Diagnose                            (knx.getGroupObject(BASE_KoDiagnose))
// Sommerzeit aktiv
#define KoBASE_IsSummertime                        (knx.getGroupObject(BASE_KoIsSummertime))
// Speichern
#define KoBASE_ManualSave                          (knx.getGroupObject(BASE_KoManualSave))
// Uhrzeit/Datum
#define KoBASE_DateTime                            (knx.getGroupObject(BASE_KoDateTime))



#define BRI_HomeKitEnabled                      46      // 1 Bit, Bit 7
#define     BRI_HomeKitEnabledMask 0x80
#define     BRI_HomeKitEnabledShift 7
#define BRI_HueEnabled                          46      // 1 Bit, Bit 6
#define     BRI_HueEnabledMask 0x40
#define     BRI_HueEnabledShift 6
#define BRI_VisibleChannels                     47      // uint8_t
#define BRI_BridgeName                          48      // char*, 25 Byte
#define BRI_PairingCode                         74      // char*, 8 Byte

// Apple HomeKit
#define ParamBRI_HomeKitEnabled                      ((bool)(knx.paramByte(BRI_HomeKitEnabled) & BRI_HomeKitEnabledMask))
// Hue Emulation (Nur für Alexa)
#define ParamBRI_HueEnabled                          ((bool)(knx.paramByte(BRI_HueEnabled) & BRI_HueEnabledMask))
// Verfügbare Geräte
#define ParamBRI_VisibleChannels                     (knx.paramByte(BRI_VisibleChannels))
// Name
#define ParamBRI_BridgeName                          (knx.paramData(BRI_BridgeName))
// Kopplungscode
#define ParamBRI_PairingCode                         (knx.paramData(BRI_PairingCode))

#define BRI_ChannelCount 50

// Parameter per channel
#define BRI_ParamBlockOffset 83
#define BRI_ParamBlockSize 58
#define BRI_ParamCalcIndex(index) (index + BRI_ParamBlockOffset + _channelIndex * BRI_ParamBlockSize)

#define BRI_CHDeviceType                         0      // 8 Bits, Bit 7-0
#define BRI_CHDeviceName                         1      // char*, 25 Byte
#define BRI_CHDisableChannel                    27      // 1 Bit, Bit 7
#define     BRI_CHDisableChannelMask 0x80
#define     BRI_CHDisableChannelShift 7
#define BRI_CHIcon                              28      // 1 Bit, Bit 7
#define     BRI_CHIconMask 0x80
#define     BRI_CHIconShift 7
#define BRI_CHIconCol0                          28      // 1 Bit, Bit 6
#define     BRI_CHIconCol0Mask 0x40
#define     BRI_CHIconCol0Shift 6
#define BRI_CHIconCol50                         28      // 1 Bit, Bit 5
#define     BRI_CHIconCol50Mask 0x20
#define     BRI_CHIconCol50Shift 5
#define BRI_CHIconCol100                        28      // 1 Bit, Bit 4
#define     BRI_CHIconCol100Mask 0x10
#define     BRI_CHIconCol100Shift 4
#define BRI_CHIcon0                             29      // char*, 8 Byte
#define BRI_CHIcon50                            37      // char*, 8 Byte
#define BRI_CHIcon100                           45      // char*, 8 Byte
#define BRI_CHSwitchHueEmulation                53      // 1 Bit, Bit 7
#define     BRI_CHSwitchHueEmulationMask 0x80
#define     BRI_CHSwitchHueEmulationShift 7
#define BRI_CHLightHueEmulation                 53      // 1 Bit, Bit 7
#define     BRI_CHLightHueEmulationMask 0x80
#define     BRI_CHLightHueEmulationShift 7
#define BRI_CHLightRGBUseSwitchKO               53      // 1 Bit, Bit 6
#define     BRI_CHLightRGBUseSwitchKOMask 0x40
#define     BRI_CHLightRGBUseSwitchKOShift 6
#define BRI_CHLightType                         53      // 4 Bits, Bit 3-0
#define     BRI_CHLightTypeMask 0x0F
#define     BRI_CHLightTypeShift 0
#define BRI_CHLightSwitchOnBehavior             54      // 8 Bits, Bit 7-0
#define BRI_CHLightSwitchOn2Behavior            55      // 8 Bits, Bit 7-0
#define BRI_CHLightRGBSwitchOnBehavior          56      // 8 Bits, Bit 7-0
#define BRI_CHLightRGBSwitchOn2Behavior         57      // 8 Bits, Bit 7-0
#define BRI_CHJalousieHueEmulation              53      // 1 Bit, Bit 7
#define     BRI_CHJalousieHueEmulationMask 0x80
#define     BRI_CHJalousieHueEmulationShift 7
#define BRI_CHJalousieUseStop                   53      // 1 Bit, Bit 6
#define     BRI_CHJalousieUseStopMask 0x40
#define     BRI_CHJalousieUseStopShift 6
#define BRI_CHJalousieUpDownHandling            53      // 4 Bits, Bit 3-0
#define     BRI_CHJalousieUpDownHandlingMask 0x0F
#define     BRI_CHJalousieUpDownHandlingShift 0
#define BRI_CHSlatHandling                      54      // 4 Bits, Bit 7-4
#define     BRI_CHSlatHandlingMask 0xF0
#define     BRI_CHSlatHandlingShift 4
#define BRI_CHThermostatTemperaturUnitType      53      // 1 Bit, Bit 7
#define     BRI_CHThermostatTemperaturUnitTypeMask 0x80
#define     BRI_CHThermostatTemperaturUnitTypeShift 7
#define BRI_CHThermostatKoModeHeating           53      // 1 Bit, Bit 6
#define     BRI_CHThermostatKoModeHeatingMask 0x40
#define     BRI_CHThermostatKoModeHeatingShift 6
#define BRI_CHThermostatKoModeHeatingFeedback   53      // 1 Bit, Bit 5
#define     BRI_CHThermostatKoModeHeatingFeedbackMask 0x20
#define     BRI_CHThermostatKoModeHeatingFeedbackShift 5
#define BRI_CHThemostateHeatingFeedbackKoType   53      // 1 Bit, Bit 4
#define     BRI_CHThemostateHeatingFeedbackKoTypeMask 0x10
#define     BRI_CHThemostateHeatingFeedbackKoTypeShift 4
#define BRI_CHThermostatMode                    53      // 4 Bits, Bit 3-0
#define     BRI_CHThermostatModeMask 0x0F
#define     BRI_CHThermostatModeShift 0
#define BRI_CHThermostatKoModeCooling           54      // 1 Bit, Bit 7
#define     BRI_CHThermostatKoModeCoolingMask 0x80
#define     BRI_CHThermostatKoModeCoolingShift 7
#define BRI_CHThermostatKoModeCoolingFeedback   54      // 1 Bit, Bit 6
#define     BRI_CHThermostatKoModeCoolingFeedbackMask 0x40
#define     BRI_CHThermostatKoModeCoolingFeedbackShift 6
#define BRI_CHThemostateCoolingFeedbackKoType   54      // 1 Bit, Bit 5
#define     BRI_CHThemostateCoolingFeedbackKoTypeMask 0x20
#define     BRI_CHThemostateCoolingFeedbackKoTypeShift 5
#define BRI_CHContactAlarmSensorInvert          53      // 1 Bit, Bit 7
#define     BRI_CHContactAlarmSensorInvertMask 0x80
#define     BRI_CHContactAlarmSensorInvertShift 7
#define BRI_CHDisplayType                       53      // 8 Bits, Bit 7-0
#define BRI_CHFanHueEmulation                   53      // 1 Bit, Bit 7
#define     BRI_CHFanHueEmulationMask 0x80
#define     BRI_CHFanHueEmulationShift 7
#define BRI_CHFanAutomatic                      53      // 1 Bit, Bit 6
#define     BRI_CHFanAutomaticMask 0x40
#define     BRI_CHFanAutomaticShift 6
#define BRI_CHFanKoAutomatic                    53      // 1 Bit, Bit 5
#define     BRI_CHFanKoAutomaticMask 0x20
#define     BRI_CHFanKoAutomaticShift 5
#define BRI_CHFanKoAutomaticFeedback            53      // 1 Bit, Bit 4
#define     BRI_CHFanKoAutomaticFeedbackMask 0x10
#define     BRI_CHFanKoAutomaticFeedbackShift 4
#define BRI_CHDoorHueEmulation                  53      // 1 Bit, Bit 7
#define     BRI_CHDoorHueEmulationMask 0x80
#define     BRI_CHDoorHueEmulationShift 7
#define BRI_CHDoorWindowMotor                   53      // 1 Bit, Bit 6
#define     BRI_CHDoorWindowMotorMask 0x40
#define     BRI_CHDoorWindowMotorShift 6
#define BRI_CHDoorWindowObstructionDetection    53      // 1 Bit, Bit 5
#define     BRI_CHDoorWindowObstructionDetectionMask 0x20
#define     BRI_CHDoorWindowObstructionDetectionShift 5
#define BRI_CHDoorWindowUpDownHandling          53      // 4 Bits, Bit 3-0
#define     BRI_CHDoorWindowUpDownHandlingMask 0x0F
#define     BRI_CHDoorWindowUpDownHandlingShift 0
#define BRI_CHDoorWindowUseStop                 54      // 1 Bit, Bit 7
#define     BRI_CHDoorWindowUseStopMask 0x80
#define     BRI_CHDoorWindowUseStopShift 7
#define BRI_CHDoorWindowFeedbackType            54      // 4 Bits, Bit 3-0
#define     BRI_CHDoorWindowFeedbackTypeMask 0x0F
#define     BRI_CHDoorWindowFeedbackTypeShift 0

// Type
#define ParamBRI_CHDeviceType                        (knx.paramByte(BRI_ParamCalcIndex(BRI_CHDeviceType)))
// Name
#define ParamBRI_CHDeviceName                        (knx.paramData(BRI_ParamCalcIndex(BRI_CHDeviceName)))
// Gerät deaktivieren (Konfiguration bleibt erhalten)
#define ParamBRI_CHDisableChannel                    ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHDisableChannel)) & BRI_CHDisableChannelMask))
// Benutzerdefiniertes Bild
#define ParamBRI_CHIcon                              ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHIcon)) & BRI_CHIconMask))
// Anzeigemodus und Statuseinfärbung
#define ParamBRI_CHIconCol0                          ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHIconCol0)) & BRI_CHIconCol0Mask))
// Anzeigemodus und Statuseinfärbung
#define ParamBRI_CHIconCol50                         ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHIconCol50)) & BRI_CHIconCol50Mask))
// Anzeigemodus und Statuseinfärbung
#define ParamBRI_CHIconCol100                        ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHIconCol100)) & BRI_CHIconCol100Mask))
// Bilddatei
#define ParamBRI_CHIcon0                             (knx.paramData(BRI_ParamCalcIndex(BRI_CHIcon0)))
// Bilddatei
#define ParamBRI_CHIcon50                            (knx.paramData(BRI_ParamCalcIndex(BRI_CHIcon50)))
// Bilddatei
#define ParamBRI_CHIcon100                           (knx.paramData(BRI_ParamCalcIndex(BRI_CHIcon100)))
// Gerät in Hue verwenden
#define ParamBRI_CHSwitchHueEmulation                ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHSwitchHueEmulation)) & BRI_CHSwitchHueEmulationMask))
// Lampe in Hue verwenden
#define ParamBRI_CHLightHueEmulation                 ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHLightHueEmulation)) & BRI_CHLightHueEmulationMask))
// KO für Schalten verwenden
#define ParamBRI_CHLightRGBUseSwitchKO               ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHLightRGBUseSwitchKO)) & BRI_CHLightRGBUseSwitchKOMask))
// Lampenart
#define ParamBRI_CHLightType                         (knx.paramByte(BRI_ParamCalcIndex(BRI_CHLightType)) & BRI_CHLightTypeMask)
// Bei EIN Befehl
#define ParamBRI_CHLightSwitchOnBehavior             (knx.paramByte(BRI_ParamCalcIndex(BRI_CHLightSwitchOnBehavior)))
// Bei EIN wenn aktuelle Helligkeit > 0%
#define ParamBRI_CHLightSwitchOn2Behavior            (knx.paramByte(BRI_ParamCalcIndex(BRI_CHLightSwitchOn2Behavior)))
// Bei EIN Befehl
#define ParamBRI_CHLightRGBSwitchOnBehavior          (knx.paramByte(BRI_ParamCalcIndex(BRI_CHLightRGBSwitchOnBehavior)))
// Bei EIN wenn aktuelle Farbe > 0
#define ParamBRI_CHLightRGBSwitchOn2Behavior         (knx.paramByte(BRI_ParamCalcIndex(BRI_CHLightRGBSwitchOn2Behavior)))
// In HUE als dimmbare Lampe darstellen
#define ParamBRI_CHJalousieHueEmulation              ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHJalousieHueEmulation)) & BRI_CHJalousieHueEmulationMask))
// Stopp Objekt verwenden
#define ParamBRI_CHJalousieUseStop                   ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHJalousieUseStop)) & BRI_CHJalousieUseStopMask))
// Auf/Ab Objekt verwenden
#define ParamBRI_CHJalousieUpDownHandling            (knx.paramByte(BRI_ParamCalcIndex(BRI_CHJalousieUpDownHandling)) & BRI_CHJalousieUpDownHandlingMask)
// Lamellenposition bei Fahrt
#define ParamBRI_CHSlatHandling                      ((knx.paramByte(BRI_ParamCalcIndex(BRI_CHSlatHandling)) & BRI_CHSlatHandlingMask) >> BRI_CHSlatHandlingShift)
// Einheit
#define ParamBRI_CHThermostatTemperaturUnitType      ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHThermostatTemperaturUnitType)) & BRI_CHThermostatTemperaturUnitTypeMask))
// Betriebsart
#define ParamBRI_CHThermostatKoModeHeating           ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHThermostatKoModeHeating)) & BRI_CHThermostatKoModeHeatingMask))
// Betriebsart Rückmeldung
#define ParamBRI_CHThermostatKoModeHeatingFeedback   ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHThermostatKoModeHeatingFeedback)) & BRI_CHThermostatKoModeHeatingFeedbackMask))
// Heizen aktiv Rückmeldung
#define ParamBRI_CHThemostateHeatingFeedbackKoType   ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHThemostateHeatingFeedbackKoType)) & BRI_CHThemostateHeatingFeedbackKoTypeMask))
// Optionen
#define ParamBRI_CHThermostatMode                    (knx.paramByte(BRI_ParamCalcIndex(BRI_CHThermostatMode)) & BRI_CHThermostatModeMask)
// Betriebsart
#define ParamBRI_CHThermostatKoModeCooling           ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHThermostatKoModeCooling)) & BRI_CHThermostatKoModeCoolingMask))
// Betriebsart Rückmeldung
#define ParamBRI_CHThermostatKoModeCoolingFeedback   ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHThermostatKoModeCoolingFeedback)) & BRI_CHThermostatKoModeCoolingFeedbackMask))
// Kühlen aktiv Rückmeldung
#define ParamBRI_CHThemostateCoolingFeedbackKoType   ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHThemostateCoolingFeedbackKoType)) & BRI_CHThemostateCoolingFeedbackKoTypeMask))
// Eingang Invertieren
#define ParamBRI_CHContactAlarmSensorInvert          ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHContactAlarmSensorInvert)) & BRI_CHContactAlarmSensorInvertMask))
// Messwert
#define ParamBRI_CHDisplayType                       (knx.paramByte(BRI_ParamCalcIndex(BRI_CHDisplayType)))
// Lüfter in HUE als Lampe darstellen
#define ParamBRI_CHFanHueEmulation                   ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHFanHueEmulation)) & BRI_CHFanHueEmulationMask))
// Lüfter hat Automatikmodus
#define ParamBRI_CHFanAutomatic                      ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHFanAutomatic)) & BRI_CHFanAutomaticMask))
// Objekt für Automatik
#define ParamBRI_CHFanKoAutomatic                    ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHFanKoAutomatic)) & BRI_CHFanKoAutomaticMask))
// Objekt für Rückmeldung
#define ParamBRI_CHFanKoAutomaticFeedback            ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHFanKoAutomaticFeedback)) & BRI_CHFanKoAutomaticFeedbackMask))
// In Hue als dimmbare Lampe darstellen
#define ParamBRI_CHDoorHueEmulation                  ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHDoorHueEmulation)) & BRI_CHDoorHueEmulationMask))
// Motorantrieb
#define ParamBRI_CHDoorWindowMotor                   ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHDoorWindowMotor)) & BRI_CHDoorWindowMotorMask))
// Blockadenerkennung
#define ParamBRI_CHDoorWindowObstructionDetection    ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHDoorWindowObstructionDetection)) & BRI_CHDoorWindowObstructionDetectionMask))
// Auf/Ab Objekt verwenden
#define ParamBRI_CHDoorWindowUpDownHandling          (knx.paramByte(BRI_ParamCalcIndex(BRI_CHDoorWindowUpDownHandling)) & BRI_CHDoorWindowUpDownHandlingMask)
// Stopp Objekt verwenden
#define ParamBRI_CHDoorWindowUseStop                 ((bool)(knx.paramByte(BRI_ParamCalcIndex(BRI_CHDoorWindowUseStop)) & BRI_CHDoorWindowUseStopMask))
// Rückmeldung
#define ParamBRI_CHDoorWindowFeedbackType            (knx.paramByte(BRI_ParamCalcIndex(BRI_CHDoorWindowFeedbackType)) & BRI_CHDoorWindowFeedbackTypeMask)

// deprecated
#define BRI_KoOffset 600

// Communication objects per channel (multiple occurrence)
#define BRI_KoBlockOffset 600
#define BRI_KoBlockSize 9

#define BRI_KoCalcNumber(index) (index + BRI_KoBlockOffset + _channelIndex * BRI_KoBlockSize)
#define BRI_KoCalcIndex(number) ((number >= BRI_KoCalcNumber(0) && number < BRI_KoCalcNumber(BRI_KoBlockSize)) ? (number - BRI_KoBlockOffset) % BRI_KoBlockSize : -1)
#define BRI_KoCalcChannel(number) ((number >= BRI_KoBlockOffset && number < BRI_KoBlockOffset + BRI_ChannelCount * BRI_KoBlockSize) ? (number - BRI_KoBlockOffset) / BRI_KoBlockSize : -1)

#define BRI_KoKO1_ 0
#define BRI_KoKO2_ 1
#define BRI_KoKO3_ 2
#define BRI_KoKO4_ 3
#define BRI_KoKO5_ 4
#define BRI_KoKO6_ 5
#define BRI_KoKO7_ 6
#define BRI_KoKO8_ 7
#define BRI_KoKO9_ 8

// KO1 %C%
#define KoBRI_KO1_                                (knx.getGroupObject(BRI_KoCalcNumber(BRI_KoKO1_)))
// KO2 %C%
#define KoBRI_KO2_                                (knx.getGroupObject(BRI_KoCalcNumber(BRI_KoKO2_)))
// KO3 %C%
#define KoBRI_KO3_                                (knx.getGroupObject(BRI_KoCalcNumber(BRI_KoKO3_)))
// KO4 %C%
#define KoBRI_KO4_                                (knx.getGroupObject(BRI_KoCalcNumber(BRI_KoKO4_)))
// KO5 %C%
#define KoBRI_KO5_                                (knx.getGroupObject(BRI_KoCalcNumber(BRI_KoKO5_)))
// KO6 %C%
#define KoBRI_KO6_                                (knx.getGroupObject(BRI_KoCalcNumber(BRI_KoKO6_)))
// KO7 %C%
#define KoBRI_KO7_                                (knx.getGroupObject(BRI_KoCalcNumber(BRI_KoKO7_)))
// KO8 %C%
#define KoBRI_KO8_                                (knx.getGroupObject(BRI_KoCalcNumber(BRI_KoKO8_)))
// KO9 %C%
#define KoBRI_KO9_                                (knx.getGroupObject(BRI_KoCalcNumber(BRI_KoKO9_)))

#define TCH_VisibleChannels                     2983      // uint8_t
#define TCH_DefaultPage                         2984      // uint8_t
#define TCH_DefaultPageDelayBase                2985      // 2 Bits, Bit 7-6
#define     TCH_DefaultPageDelayBaseMask 0xC0
#define     TCH_DefaultPageDelayBaseShift 6
#define TCH_DefaultPageDelayTime                2985      // 14 Bits, Bit 13-0
#define     TCH_DefaultPageDelayTimeMask 0x3FFF
#define     TCH_DefaultPageDelayTimeShift 0
#define TCH_DefaultPageKO                       2987      // 1 Bit, Bit 7
#define     TCH_DefaultPageKOMask 0x80
#define     TCH_DefaultPageKOShift 7
#define TCH_SensorKeys                          2987      // 1 Bit, Bit 6
#define     TCH_SensorKeysMask 0x40
#define     TCH_SensorKeysShift 6
#define TCH_LeftRightChanged                    2987      // 1 Bit, Bit 5
#define     TCH_LeftRightChangedMask 0x20
#define     TCH_LeftRightChangedShift 5
#define TCH_Slide                               2991      // 1 Bit, Bit 4
#define     TCH_SlideMask 0x10
#define     TCH_SlideShift 4
#define TCH_DayNightObject                      2987      // 4 Bits, Bit 3-0
#define     TCH_DayNightObjectMask 0x0F
#define     TCH_DayNightObjectShift 0
#define TCH_SwitchOffDeleayBase                 2988      // 2 Bits, Bit 7-6
#define     TCH_SwitchOffDeleayBaseMask 0xC0
#define     TCH_SwitchOffDeleayBaseShift 6
#define TCH_SwitchOffDelayTime                  2988      // 14 Bits, Bit 13-0
#define     TCH_SwitchOffDelayTimeMask 0x3FFF
#define     TCH_SwitchOffDelayTimeShift 0
#define TCH_ThemeDay                            2990      // 4 Bits, Bit 7-4
#define     TCH_ThemeDayMask 0xF0
#define     TCH_ThemeDayShift 4
#define TCH_ThemeNight                          2990      // 4 Bits, Bit 3-0
#define     TCH_ThemeNightMask 0x0F
#define     TCH_ThemeNightShift 0
#define TCH_DisplayRotation                     2991      // 4 Bits, Bit 7-4
#define     TCH_DisplayRotationMask 0xF0
#define     TCH_DisplayRotationShift 4

// Verfügbare Seiten
#define ParamTCH_VisibleChannels                     (knx.paramByte(TCH_VisibleChannels))
// Standard Seite
#define ParamTCH_DefaultPage                         (knx.paramByte(TCH_DefaultPage))
// Standardseite nach Zeitbasis
#define ParamTCH_DefaultPageDelayBase                ((knx.paramByte(TCH_DefaultPageDelayBase) & TCH_DefaultPageDelayBaseMask) >> TCH_DefaultPageDelayBaseShift)
// Standardseite nach Zeit
#define ParamTCH_DefaultPageDelayTime                (knx.paramWord(TCH_DefaultPageDelayTime) & TCH_DefaultPageDelayTimeMask)
// Standardseite nach Zeit (in Millisekunden)
#define ParamTCH_DefaultPageDelayTimeMS              (paramDelay(knx.paramWord(TCH_DefaultPageDelayTime)))
// Gruppenobjekt für Standard Seitenauswahl
#define ParamTCH_DefaultPageKO                       ((bool)(knx.paramByte(TCH_DefaultPageKO) & TCH_DefaultPageKOMask))
// Sensor Tasten Vorhanden
#define ParamTCH_SensorKeys                          ((bool)(knx.paramByte(TCH_SensorKeys) & TCH_SensorKeysMask))
// Links-Rechts tauschen
#define ParamTCH_LeftRightChanged                    ((bool)(knx.paramByte(TCH_LeftRightChanged) & TCH_LeftRightChangedMask))
// Seitenwechsel über Wischen im unteren Bereich
#define ParamTCH_Slide                               ((bool)(knx.paramByte(TCH_Slide) & TCH_SlideMask))
// Bei Nacht anders
#define ParamTCH_DayNightObject                      (knx.paramByte(TCH_DayNightObject) & TCH_DayNightObjectMask)
// Anzeige aus nach Zeitbasis
#define ParamTCH_SwitchOffDeleayBase                 ((knx.paramByte(TCH_SwitchOffDeleayBase) & TCH_SwitchOffDeleayBaseMask) >> TCH_SwitchOffDeleayBaseShift)
// Anzeige aus nach Zeit
#define ParamTCH_SwitchOffDelayTime                  (knx.paramWord(TCH_SwitchOffDelayTime) & TCH_SwitchOffDelayTimeMask)
// Anzeige aus nach Zeit (in Millisekunden)
#define ParamTCH_SwitchOffDelayTimeMS                (paramDelay(knx.paramWord(TCH_SwitchOffDelayTime)))
// Standard
#define ParamTCH_ThemeDay                            ((knx.paramByte(TCH_ThemeDay) & TCH_ThemeDayMask) >> TCH_ThemeDayShift)
// Nacht
#define ParamTCH_ThemeNight                          (knx.paramByte(TCH_ThemeNight) & TCH_ThemeNightMask)
// Anzeige drehen
#define ParamTCH_DisplayRotation                     ((knx.paramByte(TCH_DisplayRotation) & TCH_DisplayRotationMask) >> TCH_DisplayRotationShift)

#define TCH_KoDisplayOnOff 500
#define TCH_KoDisplayOnOffState 501
#define TCH_KoPage 502
#define TCH_KoCurrentPage 503
#define TCH_KoPrevNext 504
#define TCH_KoDefaultPage 505
#define TCH_KoDayNight 506
#define TCH_KoPageEnabledA 507
#define TCH_KoPageEnabledB 508
#define TCH_KoPageEnabledC 509
#define TCH_KoPageEnabledD 510
#define TCH_KoPageEnabledE 511
#define TCH_KoPageEnabledF 512
#define TCH_KoPageEnabledG 513
#define TCH_KoPageEnabledH 514

// Display Einschalten
#define KoTCH_DisplayOnOff                        (knx.getGroupObject(TCH_KoDisplayOnOff))
// Display Eingeschalten
#define KoTCH_DisplayOnOffState                   (knx.getGroupObject(TCH_KoDisplayOnOffState))
// Gehe zu Seite
#define KoTCH_Page                                (knx.getGroupObject(TCH_KoPage))
// Aktuelle Seite
#define KoTCH_CurrentPage                         (knx.getGroupObject(TCH_KoCurrentPage))
// Blättern
#define KoTCH_PrevNext                            (knx.getGroupObject(TCH_KoPrevNext))
// Standardseite
#define KoTCH_DefaultPage                         (knx.getGroupObject(TCH_KoDefaultPage))
// Tag/Nacht
#define KoTCH_DayNight                            (knx.getGroupObject(TCH_KoDayNight))
// Seitenfreigabe A
#define KoTCH_PageEnabledA                        (knx.getGroupObject(TCH_KoPageEnabledA))
// Seitenfreigabe B
#define KoTCH_PageEnabledB                        (knx.getGroupObject(TCH_KoPageEnabledB))
// Seitenfreigabe C
#define KoTCH_PageEnabledC                        (knx.getGroupObject(TCH_KoPageEnabledC))
// Seitenfreigabe D
#define KoTCH_PageEnabledD                        (knx.getGroupObject(TCH_KoPageEnabledD))
// Seitenfreigabe E
#define KoTCH_PageEnabledE                        (knx.getGroupObject(TCH_KoPageEnabledE))
// Seitenfreigabe F
#define KoTCH_PageEnabledF                        (knx.getGroupObject(TCH_KoPageEnabledF))
// Seitenfreigabe G
#define KoTCH_PageEnabledG                        (knx.getGroupObject(TCH_KoPageEnabledG))
// Seitenfreigabe H
#define KoTCH_PageEnabledH                        (knx.getGroupObject(TCH_KoPageEnabledH))

#define TCH_ChannelCount 50

// Parameter per channel
#define TCH_ParamBlockOffset 2992
#define TCH_ParamBlockSize 59
#define TCH_ParamCalcIndex(index) (index + TCH_ParamBlockOffset + _channelIndex * TCH_ParamBlockSize)

#define TCH_CHPageType                           0      // 8 Bits, Bit 7-0
#define TCH_CHNavigation                         1      // 1 Bit, Bit 7
#define     TCH_CHNavigationMask 0x80
#define     TCH_CHNavigationShift 7
#define TCH_CHPageEnabled                        1      // 4 Bits, Bit 4-1
#define     TCH_CHPageEnabledMask 0x1E
#define     TCH_CHPageEnabledShift 1
#define TCH_CHNumbeOfFields                      2      // 8 Bits, Bit 7-0
#define TCH_CHPageName                           3      // char*, 25 Byte
#define TCH_CHIconSelection                     29      // 8 Bits, Bit 7-0
#define TCH_CHIconName                          30      // char*, 8 Byte
#define TCH_CHDevicePageType                    38      // 4 Bits, Bit 7-4
#define     TCH_CHDevicePageTypeMask 0xF0
#define     TCH_CHDevicePageTypeShift 4
#define TCH_CHDeviceSelection1                  39      // 8 Bits, Bit 7-0
#define TCH_CHShortPress1                       40      // 4 Bits, Bit 7-4
#define     TCH_CHShortPress1Mask 0xF0
#define     TCH_CHShortPress1Shift 4
#define TCH_CHLongPress1                        40      // 4 Bits, Bit 3-0
#define     TCH_CHLongPress1Mask 0x0F
#define     TCH_CHLongPress1Shift 0
#define TCH_CHJumpToShort1                      41      // uint8_t
#define TCH_CHJumpToLong1                       42      // uint8_t
#define TCH_CHTCHCellType1                      43      // 8 Bits, Bit 7-0
#define TCH_CHDeviceSelection2                  44      // 8 Bits, Bit 7-0
#define TCH_CHShortPress2                       45      // 4 Bits, Bit 7-4
#define     TCH_CHShortPress2Mask 0xF0
#define     TCH_CHShortPress2Shift 4
#define TCH_CHLongPress2                        45      // 4 Bits, Bit 3-0
#define     TCH_CHLongPress2Mask 0x0F
#define     TCH_CHLongPress2Shift 0
#define TCH_CHJumpToShort2                      46      // uint8_t
#define TCH_CHJumpToLong2                       47      // uint8_t
#define TCH_CHTCHCellType2                      48      // 8 Bits, Bit 7-0
#define TCH_CHDeviceSelection3                  49      // 8 Bits, Bit 7-0
#define TCH_CHShortPress3                       50      // 4 Bits, Bit 7-4
#define     TCH_CHShortPress3Mask 0xF0
#define     TCH_CHShortPress3Shift 4
#define TCH_CHLongPress3                        50      // 4 Bits, Bit 3-0
#define     TCH_CHLongPress3Mask 0x0F
#define     TCH_CHLongPress3Shift 0
#define TCH_CHJumpToShort3                      51      // uint8_t
#define TCH_CHJumpToLong3                       52      // uint8_t
#define TCH_CHTCHCellType3                      53      // 8 Bits, Bit 7-0
#define TCH_CHDeviceSelection4                  54      // 8 Bits, Bit 7-0
#define TCH_CHShortPress4                       55      // 4 Bits, Bit 7-4
#define     TCH_CHShortPress4Mask 0xF0
#define     TCH_CHShortPress4Shift 4
#define TCH_CHLongPress4                        55      // 4 Bits, Bit 3-0
#define     TCH_CHLongPress4Mask 0x0F
#define     TCH_CHLongPress4Shift 0
#define TCH_CHJumpToShort4                      56      // uint8_t
#define TCH_CHJumpToLong4                       57      // uint8_t
#define TCH_CHTCHCellType4                      58      // 8 Bits, Bit 7-0

// Seitentyp
#define ParamTCH_CHPageType                          (knx.paramByte(TCH_ParamCalcIndex(TCH_CHPageType)))
// Seite über Blättern erreichbar
#define ParamTCH_CHNavigation                        ((bool)(knx.paramByte(TCH_ParamCalcIndex(TCH_CHNavigation)) & TCH_CHNavigationMask))
// Seitefreigabe über Objekt
#define ParamTCH_CHPageEnabled                       ((knx.paramByte(TCH_ParamCalcIndex(TCH_CHPageEnabled)) & TCH_CHPageEnabledMask) >> TCH_CHPageEnabledShift)
// Layout
#define ParamTCH_CHNumbeOfFields                     (knx.paramByte(TCH_ParamCalcIndex(TCH_CHNumbeOfFields)))
// Name
#define ParamTCH_CHPageName                          (knx.paramData(TCH_ParamCalcIndex(TCH_CHPageName)))
// Bild
#define ParamTCH_CHIconSelection                     (knx.paramByte(TCH_ParamCalcIndex(TCH_CHIconSelection)))
// Bilddatei
#define ParamTCH_CHIconName                          (knx.paramData(TCH_ParamCalcIndex(TCH_CHIconName)))
// Anzeige
#define ParamTCH_CHDevicePageType                    ((knx.paramByte(TCH_ParamCalcIndex(TCH_CHDevicePageType)) & TCH_CHDevicePageTypeMask) >> TCH_CHDevicePageTypeShift)
// Gerät
#define ParamTCH_CHDeviceSelection1                  (knx.paramByte(TCH_ParamCalcIndex(TCH_CHDeviceSelection1)))
// Kurzer Druck
#define ParamTCH_CHShortPress1                       ((knx.paramByte(TCH_ParamCalcIndex(TCH_CHShortPress1)) & TCH_CHShortPress1Mask) >> TCH_CHShortPress1Shift)
// Langer Druck
#define ParamTCH_CHLongPress1                        (knx.paramByte(TCH_ParamCalcIndex(TCH_CHLongPress1)) & TCH_CHLongPress1Mask)
// Absprung zu
#define ParamTCH_CHJumpToShort1                      (knx.paramByte(TCH_ParamCalcIndex(TCH_CHJumpToShort1)))
// Absprung zu
#define ParamTCH_CHJumpToLong1                       (knx.paramByte(TCH_ParamCalcIndex(TCH_CHJumpToLong1)))
// Funktion
#define ParamTCH_CHTCHCellType1                      (knx.paramByte(TCH_ParamCalcIndex(TCH_CHTCHCellType1)))
// Gerät
#define ParamTCH_CHDeviceSelection2                  (knx.paramByte(TCH_ParamCalcIndex(TCH_CHDeviceSelection2)))
// Kurzer Druck
#define ParamTCH_CHShortPress2                       ((knx.paramByte(TCH_ParamCalcIndex(TCH_CHShortPress2)) & TCH_CHShortPress2Mask) >> TCH_CHShortPress2Shift)
// Langer Druck
#define ParamTCH_CHLongPress2                        (knx.paramByte(TCH_ParamCalcIndex(TCH_CHLongPress2)) & TCH_CHLongPress2Mask)
// Absprung zu
#define ParamTCH_CHJumpToShort2                      (knx.paramByte(TCH_ParamCalcIndex(TCH_CHJumpToShort2)))
// Absprung zu
#define ParamTCH_CHJumpToLong2                       (knx.paramByte(TCH_ParamCalcIndex(TCH_CHJumpToLong2)))
// Funktion
#define ParamTCH_CHTCHCellType2                      (knx.paramByte(TCH_ParamCalcIndex(TCH_CHTCHCellType2)))
// Gerät
#define ParamTCH_CHDeviceSelection3                  (knx.paramByte(TCH_ParamCalcIndex(TCH_CHDeviceSelection3)))
// Kurzer Druck
#define ParamTCH_CHShortPress3                       ((knx.paramByte(TCH_ParamCalcIndex(TCH_CHShortPress3)) & TCH_CHShortPress3Mask) >> TCH_CHShortPress3Shift)
// Langer Druck
#define ParamTCH_CHLongPress3                        (knx.paramByte(TCH_ParamCalcIndex(TCH_CHLongPress3)) & TCH_CHLongPress3Mask)
// Absprung zu
#define ParamTCH_CHJumpToShort3                      (knx.paramByte(TCH_ParamCalcIndex(TCH_CHJumpToShort3)))
// Absprung zu
#define ParamTCH_CHJumpToLong3                       (knx.paramByte(TCH_ParamCalcIndex(TCH_CHJumpToLong3)))
// Funktion
#define ParamTCH_CHTCHCellType3                      (knx.paramByte(TCH_ParamCalcIndex(TCH_CHTCHCellType3)))
// Gerät
#define ParamTCH_CHDeviceSelection4                  (knx.paramByte(TCH_ParamCalcIndex(TCH_CHDeviceSelection4)))
// Kurzer Druck
#define ParamTCH_CHShortPress4                       ((knx.paramByte(TCH_ParamCalcIndex(TCH_CHShortPress4)) & TCH_CHShortPress4Mask) >> TCH_CHShortPress4Shift)
// Langer Druck
#define ParamTCH_CHLongPress4                        (knx.paramByte(TCH_ParamCalcIndex(TCH_CHLongPress4)) & TCH_CHLongPress4Mask)
// Absprung zu
#define ParamTCH_CHJumpToShort4                      (knx.paramByte(TCH_ParamCalcIndex(TCH_CHJumpToShort4)))
// Absprung zu
#define ParamTCH_CHJumpToLong4                       (knx.paramByte(TCH_ParamCalcIndex(TCH_CHJumpToLong4)))
// Funktion
#define ParamTCH_CHTCHCellType4                      (knx.paramByte(TCH_ParamCalcIndex(TCH_CHTCHCellType4)))

#define LOG_BuzzerInstalled                     5942      // 1 Bit, Bit 7
#define     LOG_BuzzerInstalledMask 0x80
#define     LOG_BuzzerInstalledShift 7
#define LOG_LedInstalled                        5942      // 1 Bit, Bit 6
#define     LOG_LedInstalledMask 0x40
#define     LOG_LedInstalledShift 6
#define LOG_VacationKo                          5942      // 1 Bit, Bit 5
#define     LOG_VacationKoMask 0x20
#define     LOG_VacationKoShift 5
#define LOG_HolidayKo                           5942      // 1 Bit, Bit 4
#define     LOG_HolidayKoMask 0x10
#define     LOG_HolidayKoShift 4
#define LOG_VacationRead                        5942      // 1 Bit, Bit 3
#define     LOG_VacationReadMask 0x08
#define     LOG_VacationReadShift 3
#define LOG_HolidaySend                         5942      // 1 Bit, Bit 2
#define     LOG_HolidaySendMask 0x04
#define     LOG_HolidaySendShift 2
#define LOG_Neujahr                             5943      // 1 Bit, Bit 7
#define     LOG_NeujahrMask 0x80
#define     LOG_NeujahrShift 7
#define LOG_DreiKoenige                         5943      // 1 Bit, Bit 6
#define     LOG_DreiKoenigeMask 0x40
#define     LOG_DreiKoenigeShift 6
#define LOG_Weiberfastnacht                     5943      // 1 Bit, Bit 5
#define     LOG_WeiberfastnachtMask 0x20
#define     LOG_WeiberfastnachtShift 5
#define LOG_Rosenmontag                         5943      // 1 Bit, Bit 4
#define     LOG_RosenmontagMask 0x10
#define     LOG_RosenmontagShift 4
#define LOG_Fastnachtsdienstag                  5943      // 1 Bit, Bit 3
#define     LOG_FastnachtsdienstagMask 0x08
#define     LOG_FastnachtsdienstagShift 3
#define LOG_Aschermittwoch                      5943      // 1 Bit, Bit 2
#define     LOG_AschermittwochMask 0x04
#define     LOG_AschermittwochShift 2
#define LOG_Frauentag                           5943      // 1 Bit, Bit 1
#define     LOG_FrauentagMask 0x02
#define     LOG_FrauentagShift 1
#define LOG_Gruendonnerstag                     5943      // 1 Bit, Bit 0
#define     LOG_GruendonnerstagMask 0x01
#define     LOG_GruendonnerstagShift 0
#define LOG_Karfreitag                          5944      // 1 Bit, Bit 7
#define     LOG_KarfreitagMask 0x80
#define     LOG_KarfreitagShift 7
#define LOG_Ostersonntag                        5944      // 1 Bit, Bit 6
#define     LOG_OstersonntagMask 0x40
#define     LOG_OstersonntagShift 6
#define LOG_Ostermontag                         5944      // 1 Bit, Bit 5
#define     LOG_OstermontagMask 0x20
#define     LOG_OstermontagShift 5
#define LOG_TagDerArbeit                        5944      // 1 Bit, Bit 4
#define     LOG_TagDerArbeitMask 0x10
#define     LOG_TagDerArbeitShift 4
#define LOG_Himmelfahrt                         5944      // 1 Bit, Bit 3
#define     LOG_HimmelfahrtMask 0x08
#define     LOG_HimmelfahrtShift 3
#define LOG_Pfingstsonntag                      5944      // 1 Bit, Bit 2
#define     LOG_PfingstsonntagMask 0x04
#define     LOG_PfingstsonntagShift 2
#define LOG_Pfingstmontag                       5944      // 1 Bit, Bit 1
#define     LOG_PfingstmontagMask 0x02
#define     LOG_PfingstmontagShift 1
#define LOG_Fronleichnam                        5944      // 1 Bit, Bit 0
#define     LOG_FronleichnamMask 0x01
#define     LOG_FronleichnamShift 0
#define LOG_Friedensfest                        5945      // 1 Bit, Bit 7
#define     LOG_FriedensfestMask 0x80
#define     LOG_FriedensfestShift 7
#define LOG_MariaHimmelfahrt                    5945      // 1 Bit, Bit 6
#define     LOG_MariaHimmelfahrtMask 0x40
#define     LOG_MariaHimmelfahrtShift 6
#define LOG_DeutscheEinheit                     5945      // 1 Bit, Bit 5
#define     LOG_DeutscheEinheitMask 0x20
#define     LOG_DeutscheEinheitShift 5
#define LOG_Reformationstag                     5945      // 1 Bit, Bit 4
#define     LOG_ReformationstagMask 0x10
#define     LOG_ReformationstagShift 4
#define LOG_Allerheiligen                       5945      // 1 Bit, Bit 3
#define     LOG_AllerheiligenMask 0x08
#define     LOG_AllerheiligenShift 3
#define LOG_BussBettag                          5945      // 1 Bit, Bit 2
#define     LOG_BussBettagMask 0x04
#define     LOG_BussBettagShift 2
#define LOG_Advent1                             5945      // 1 Bit, Bit 1
#define     LOG_Advent1Mask 0x02
#define     LOG_Advent1Shift 1
#define LOG_Advent2                             5945      // 1 Bit, Bit 0
#define     LOG_Advent2Mask 0x01
#define     LOG_Advent2Shift 0
#define LOG_Advent3                             5946      // 1 Bit, Bit 7
#define     LOG_Advent3Mask 0x80
#define     LOG_Advent3Shift 7
#define LOG_Advent4                             5946      // 1 Bit, Bit 6
#define     LOG_Advent4Mask 0x40
#define     LOG_Advent4Shift 6
#define LOG_Heiligabend                         5946      // 1 Bit, Bit 5
#define     LOG_HeiligabendMask 0x20
#define     LOG_HeiligabendShift 5
#define LOG_Weihnachtstag1                      5946      // 1 Bit, Bit 4
#define     LOG_Weihnachtstag1Mask 0x10
#define     LOG_Weihnachtstag1Shift 4
#define LOG_Weihnachtstag2                      5946      // 1 Bit, Bit 3
#define     LOG_Weihnachtstag2Mask 0x08
#define     LOG_Weihnachtstag2Shift 3
#define LOG_Silvester                           5946      // 1 Bit, Bit 2
#define     LOG_SilvesterMask 0x04
#define     LOG_SilvesterShift 2
#define LOG_Nationalfeiertag                    5946      // 1 Bit, Bit 1
#define     LOG_NationalfeiertagMask 0x02
#define     LOG_NationalfeiertagShift 1
#define LOG_MariaEmpfaengnis                    5946      // 1 Bit, Bit 0
#define     LOG_MariaEmpfaengnisMask 0x01
#define     LOG_MariaEmpfaengnisShift 0
#define LOG_NationalfeiertagSchweiz             5947      // 1 Bit, Bit 7
#define     LOG_NationalfeiertagSchweizMask 0x80
#define     LOG_NationalfeiertagSchweizShift 7
#define LOG_Totensonntag                        5947      // 1 Bit, Bit 6
#define     LOG_TotensonntagMask 0x40
#define     LOG_TotensonntagShift 6
#define LOG_BuzzerSilent                        5948      // uint16_t
#define LOG_BuzzerNormal                        5950      // uint16_t
#define LOG_BuzzerLoud                          5952      // uint16_t
#define LOG_VisibleChannels                     5954      // uint8_t
#define LOG_LedMapping                          5955      // 3 Bits, Bit 7-5
#define     LOG_LedMappingMask 0xE0
#define     LOG_LedMappingShift 5
#define LOG_UserFormula1                        5956      // char*, 99 Byte
#define LOG_UserFormula1Active                  6055      // 1 Bit, Bit 7
#define     LOG_UserFormula1ActiveMask 0x80
#define     LOG_UserFormula1ActiveShift 7
#define LOG_UserFormula2                        6056      // char*, 99 Byte
#define LOG_UserFormula2Active                  6155      // 1 Bit, Bit 7
#define     LOG_UserFormula2ActiveMask 0x80
#define     LOG_UserFormula2ActiveShift 7
#define LOG_UserFormula3                        6156      // char*, 99 Byte
#define LOG_UserFormula3Active                  6255      // 1 Bit, Bit 7
#define     LOG_UserFormula3ActiveMask 0x80
#define     LOG_UserFormula3ActiveShift 7
#define LOG_UserFormula4                        6256      // char*, 99 Byte
#define LOG_UserFormula4Active                  6355      // 1 Bit, Bit 7
#define     LOG_UserFormula4ActiveMask 0x80
#define     LOG_UserFormula4ActiveShift 7
#define LOG_UserFormula5                        6356      // char*, 99 Byte
#define LOG_UserFormula5Active                  6455      // 1 Bit, Bit 7
#define     LOG_UserFormula5ActiveMask 0x80
#define     LOG_UserFormula5ActiveShift 7
#define LOG_UserFormula6                        6456      // char*, 99 Byte
#define LOG_UserFormula6Active                  6555      // 1 Bit, Bit 7
#define     LOG_UserFormula6ActiveMask 0x80
#define     LOG_UserFormula6ActiveShift 7
#define LOG_UserFormula7                        6556      // char*, 99 Byte
#define LOG_UserFormula7Active                  6655      // 1 Bit, Bit 7
#define     LOG_UserFormula7ActiveMask 0x80
#define     LOG_UserFormula7ActiveShift 7
#define LOG_UserFormula8                        6656      // char*, 99 Byte
#define LOG_UserFormula8Active                  6755      // 1 Bit, Bit 7
#define     LOG_UserFormula8ActiveMask 0x80
#define     LOG_UserFormula8ActiveShift 7
#define LOG_UserFormula9                        6756      // char*, 99 Byte
#define LOG_UserFormula9Active                  6855      // 1 Bit, Bit 7
#define     LOG_UserFormula9ActiveMask 0x80
#define     LOG_UserFormula9ActiveShift 7
#define LOG_UserFormula10                       6856      // char*, 99 Byte
#define LOG_UserFormula10Active                 6955      // 1 Bit, Bit 7
#define     LOG_UserFormula10ActiveMask 0x80
#define     LOG_UserFormula10ActiveShift 7
#define LOG_UserFormula11                       6956      // char*, 99 Byte
#define LOG_UserFormula11Active                 7055      // 1 Bit, Bit 7
#define     LOG_UserFormula11ActiveMask 0x80
#define     LOG_UserFormula11ActiveShift 7
#define LOG_UserFormula12                       7056      // char*, 99 Byte
#define LOG_UserFormula12Active                 7155      // 1 Bit, Bit 7
#define     LOG_UserFormula12ActiveMask 0x80
#define     LOG_UserFormula12ActiveShift 7
#define LOG_UserFormula13                       7156      // char*, 99 Byte
#define LOG_UserFormula13Active                 7255      // 1 Bit, Bit 7
#define     LOG_UserFormula13ActiveMask 0x80
#define     LOG_UserFormula13ActiveShift 7
#define LOG_UserFormula14                       7256      // char*, 99 Byte
#define LOG_UserFormula14Active                 7355      // 1 Bit, Bit 7
#define     LOG_UserFormula14ActiveMask 0x80
#define     LOG_UserFormula14ActiveShift 7
#define LOG_UserFormula15                       7356      // char*, 99 Byte
#define LOG_UserFormula15Active                 7455      // 1 Bit, Bit 7
#define     LOG_UserFormula15ActiveMask 0x80
#define     LOG_UserFormula15ActiveShift 7
#define LOG_UserFormula16                       7456      // char*, 99 Byte
#define LOG_UserFormula16Active                 7555      // 1 Bit, Bit 7
#define     LOG_UserFormula16ActiveMask 0x80
#define     LOG_UserFormula16ActiveShift 7
#define LOG_UserFormula17                       7556      // char*, 99 Byte
#define LOG_UserFormula17Active                 7655      // 1 Bit, Bit 7
#define     LOG_UserFormula17ActiveMask 0x80
#define     LOG_UserFormula17ActiveShift 7
#define LOG_UserFormula18                       7656      // char*, 99 Byte
#define LOG_UserFormula18Active                 7755      // 1 Bit, Bit 7
#define     LOG_UserFormula18ActiveMask 0x80
#define     LOG_UserFormula18ActiveShift 7
#define LOG_UserFormula19                       7756      // char*, 99 Byte
#define LOG_UserFormula19Active                 7855      // 1 Bit, Bit 7
#define     LOG_UserFormula19ActiveMask 0x80
#define     LOG_UserFormula19ActiveShift 7
#define LOG_UserFormula20                       7856      // char*, 99 Byte
#define LOG_UserFormula20Active                 7955      // 1 Bit, Bit 7
#define     LOG_UserFormula20ActiveMask 0x80
#define     LOG_UserFormula20ActiveShift 7
#define LOG_UserFormula21                       7956      // char*, 99 Byte
#define LOG_UserFormula21Active                 8055      // 1 Bit, Bit 7
#define     LOG_UserFormula21ActiveMask 0x80
#define     LOG_UserFormula21ActiveShift 7
#define LOG_UserFormula22                       8056      // char*, 99 Byte
#define LOG_UserFormula22Active                 8155      // 1 Bit, Bit 7
#define     LOG_UserFormula22ActiveMask 0x80
#define     LOG_UserFormula22ActiveShift 7
#define LOG_UserFormula23                       8156      // char*, 99 Byte
#define LOG_UserFormula23Active                 8255      // 1 Bit, Bit 7
#define     LOG_UserFormula23ActiveMask 0x80
#define     LOG_UserFormula23ActiveShift 7
#define LOG_UserFormula24                       8256      // char*, 99 Byte
#define LOG_UserFormula24Active                 8355      // 1 Bit, Bit 7
#define     LOG_UserFormula24ActiveMask 0x80
#define     LOG_UserFormula24ActiveShift 7
#define LOG_UserFormula25                       8356      // char*, 99 Byte
#define LOG_UserFormula25Active                 8455      // 1 Bit, Bit 7
#define     LOG_UserFormula25ActiveMask 0x80
#define     LOG_UserFormula25ActiveShift 7
#define LOG_UserFormula26                       8456      // char*, 99 Byte
#define LOG_UserFormula26Active                 8555      // 1 Bit, Bit 7
#define     LOG_UserFormula26ActiveMask 0x80
#define     LOG_UserFormula26ActiveShift 7
#define LOG_UserFormula27                       8556      // char*, 99 Byte
#define LOG_UserFormula27Active                 8655      // 1 Bit, Bit 7
#define     LOG_UserFormula27ActiveMask 0x80
#define     LOG_UserFormula27ActiveShift 7
#define LOG_UserFormula28                       8656      // char*, 99 Byte
#define LOG_UserFormula28Active                 8755      // 1 Bit, Bit 7
#define     LOG_UserFormula28ActiveMask 0x80
#define     LOG_UserFormula28ActiveShift 7
#define LOG_UserFormula29                       8756      // char*, 99 Byte
#define LOG_UserFormula29Active                 8855      // 1 Bit, Bit 7
#define     LOG_UserFormula29ActiveMask 0x80
#define     LOG_UserFormula29ActiveShift 7
#define LOG_UserFormula30                       8856      // char*, 99 Byte
#define LOG_UserFormula30Active                 8955      // 1 Bit, Bit 7
#define     LOG_UserFormula30ActiveMask 0x80
#define     LOG_UserFormula30ActiveShift 7

// Akustischer Signalgeber vorhanden (Buzzer)?
#define ParamLOG_BuzzerInstalled                     ((bool)(knx.paramByte(LOG_BuzzerInstalled) & LOG_BuzzerInstalledMask))
// Optischer Signalgeber vorhanden (RGB-LED)?
#define ParamLOG_LedInstalled                        ((bool)(knx.paramByte(LOG_LedInstalled) & LOG_LedInstalledMask))
// Urlaubsbehandlung aktivieren?
#define ParamLOG_VacationKo                          ((bool)(knx.paramByte(LOG_VacationKo) & LOG_VacationKoMask))
// Feiertage auf dem Bus verfügbar machen?
#define ParamLOG_HolidayKo                           ((bool)(knx.paramByte(LOG_HolidayKo) & LOG_HolidayKoMask))
// Nach Neustart Urlaubsinfo lesen?
#define ParamLOG_VacationRead                        ((bool)(knx.paramByte(LOG_VacationRead) & LOG_VacationReadMask))
// Nach Neuberechnung Feiertagsinfo senden?
#define ParamLOG_HolidaySend                         ((bool)(knx.paramByte(LOG_HolidaySend) & LOG_HolidaySendMask))
// 1. Neujahr
#define ParamLOG_Neujahr                             ((bool)(knx.paramByte(LOG_Neujahr) & LOG_NeujahrMask))
// 2. Heilige Drei Könige
#define ParamLOG_DreiKoenige                         ((bool)(knx.paramByte(LOG_DreiKoenige) & LOG_DreiKoenigeMask))
// 3. Weiberfastnacht
#define ParamLOG_Weiberfastnacht                     ((bool)(knx.paramByte(LOG_Weiberfastnacht) & LOG_WeiberfastnachtMask))
// 4. Rosenmontag
#define ParamLOG_Rosenmontag                         ((bool)(knx.paramByte(LOG_Rosenmontag) & LOG_RosenmontagMask))
// 5. Fastnachtsdienstag
#define ParamLOG_Fastnachtsdienstag                  ((bool)(knx.paramByte(LOG_Fastnachtsdienstag) & LOG_FastnachtsdienstagMask))
// 6. Aschermittwoch
#define ParamLOG_Aschermittwoch                      ((bool)(knx.paramByte(LOG_Aschermittwoch) & LOG_AschermittwochMask))
// 7. Frauentag
#define ParamLOG_Frauentag                           ((bool)(knx.paramByte(LOG_Frauentag) & LOG_FrauentagMask))
// 8. Gründonnerstag
#define ParamLOG_Gruendonnerstag                     ((bool)(knx.paramByte(LOG_Gruendonnerstag) & LOG_GruendonnerstagMask))
// 9. Karfreitag
#define ParamLOG_Karfreitag                          ((bool)(knx.paramByte(LOG_Karfreitag) & LOG_KarfreitagMask))
// 10. Ostersonntag
#define ParamLOG_Ostersonntag                        ((bool)(knx.paramByte(LOG_Ostersonntag) & LOG_OstersonntagMask))
// 11. Ostermontag
#define ParamLOG_Ostermontag                         ((bool)(knx.paramByte(LOG_Ostermontag) & LOG_OstermontagMask))
// 12. Tag der Arbeit
#define ParamLOG_TagDerArbeit                        ((bool)(knx.paramByte(LOG_TagDerArbeit) & LOG_TagDerArbeitMask))
// 13. Christi Himmelfahrt
#define ParamLOG_Himmelfahrt                         ((bool)(knx.paramByte(LOG_Himmelfahrt) & LOG_HimmelfahrtMask))
// 14. Pfingstsonntag
#define ParamLOG_Pfingstsonntag                      ((bool)(knx.paramByte(LOG_Pfingstsonntag) & LOG_PfingstsonntagMask))
// 15. Pfingstmontag
#define ParamLOG_Pfingstmontag                       ((bool)(knx.paramByte(LOG_Pfingstmontag) & LOG_PfingstmontagMask))
// 16. Fronleichnam
#define ParamLOG_Fronleichnam                        ((bool)(knx.paramByte(LOG_Fronleichnam) & LOG_FronleichnamMask))
// 17. Hohes Friedensfest
#define ParamLOG_Friedensfest                        ((bool)(knx.paramByte(LOG_Friedensfest) & LOG_FriedensfestMask))
// 18. Mariä Himmelfahrt
#define ParamLOG_MariaHimmelfahrt                    ((bool)(knx.paramByte(LOG_MariaHimmelfahrt) & LOG_MariaHimmelfahrtMask))
// 19. Tag der Deutschen Einheit
#define ParamLOG_DeutscheEinheit                     ((bool)(knx.paramByte(LOG_DeutscheEinheit) & LOG_DeutscheEinheitMask))
// 20. Reformationstag
#define ParamLOG_Reformationstag                     ((bool)(knx.paramByte(LOG_Reformationstag) & LOG_ReformationstagMask))
// 21. Allerheiligen
#define ParamLOG_Allerheiligen                       ((bool)(knx.paramByte(LOG_Allerheiligen) & LOG_AllerheiligenMask))
// 22. Buß- und Bettag
#define ParamLOG_BussBettag                          ((bool)(knx.paramByte(LOG_BussBettag) & LOG_BussBettagMask))
// 23. Erster Advent
#define ParamLOG_Advent1                             ((bool)(knx.paramByte(LOG_Advent1) & LOG_Advent1Mask))
// 24. Zweiter Advent
#define ParamLOG_Advent2                             ((bool)(knx.paramByte(LOG_Advent2) & LOG_Advent2Mask))
// 25. Dritter Advent
#define ParamLOG_Advent3                             ((bool)(knx.paramByte(LOG_Advent3) & LOG_Advent3Mask))
// 26. Vierter Advent
#define ParamLOG_Advent4                             ((bool)(knx.paramByte(LOG_Advent4) & LOG_Advent4Mask))
// 27. Heiligabend
#define ParamLOG_Heiligabend                         ((bool)(knx.paramByte(LOG_Heiligabend) & LOG_HeiligabendMask))
// 28. Erster Weihnachtstag
#define ParamLOG_Weihnachtstag1                      ((bool)(knx.paramByte(LOG_Weihnachtstag1) & LOG_Weihnachtstag1Mask))
// 29. Zweiter Weihnachtstag
#define ParamLOG_Weihnachtstag2                      ((bool)(knx.paramByte(LOG_Weihnachtstag2) & LOG_Weihnachtstag2Mask))
// 30. Silvester
#define ParamLOG_Silvester                           ((bool)(knx.paramByte(LOG_Silvester) & LOG_SilvesterMask))
// 31. Nationalfeiertag (AT)
#define ParamLOG_Nationalfeiertag                    ((bool)(knx.paramByte(LOG_Nationalfeiertag) & LOG_NationalfeiertagMask))
// 32. Maria Empfängnis (AT)
#define ParamLOG_MariaEmpfaengnis                    ((bool)(knx.paramByte(LOG_MariaEmpfaengnis) & LOG_MariaEmpfaengnisMask))
// 33. Nationalfeiertag (CH)
#define ParamLOG_NationalfeiertagSchweiz             ((bool)(knx.paramByte(LOG_NationalfeiertagSchweiz) & LOG_NationalfeiertagSchweizMask))
// 34. Totensonntag
#define ParamLOG_Totensonntag                        ((bool)(knx.paramByte(LOG_Totensonntag) & LOG_TotensonntagMask))
// Frequenz für Buzzer (leise)
#define ParamLOG_BuzzerSilent                        (knx.paramWord(LOG_BuzzerSilent))
// Frequenz für Buzzer (normal)
#define ParamLOG_BuzzerNormal                        (knx.paramWord(LOG_BuzzerNormal))
// Frequenz für Buzzer (laut)
#define ParamLOG_BuzzerLoud                          (knx.paramWord(LOG_BuzzerLoud))
// Verfügbare Kanäle
#define ParamLOG_VisibleChannels                     (knx.paramByte(LOG_VisibleChannels))
// Lötpad A / B / C entspricht
#define ParamLOG_LedMapping                          ((knx.paramByte(LOG_LedMapping) & LOG_LedMappingMask) >> LOG_LedMappingShift)
// Formeldefinition
#define ParamLOG_UserFormula1                        (knx.paramData(LOG_UserFormula1))
// Benutzerformel 1 aktiv
#define ParamLOG_UserFormula1Active                  ((bool)(knx.paramByte(LOG_UserFormula1Active) & LOG_UserFormula1ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula2                        (knx.paramData(LOG_UserFormula2))
// Benutzerformel 2 aktiv
#define ParamLOG_UserFormula2Active                  ((bool)(knx.paramByte(LOG_UserFormula2Active) & LOG_UserFormula2ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula3                        (knx.paramData(LOG_UserFormula3))
// Benutzerformel 3 aktiv
#define ParamLOG_UserFormula3Active                  ((bool)(knx.paramByte(LOG_UserFormula3Active) & LOG_UserFormula3ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula4                        (knx.paramData(LOG_UserFormula4))
// Benutzerformel 4 aktiv
#define ParamLOG_UserFormula4Active                  ((bool)(knx.paramByte(LOG_UserFormula4Active) & LOG_UserFormula4ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula5                        (knx.paramData(LOG_UserFormula5))
// Benutzerformel 5 aktiv
#define ParamLOG_UserFormula5Active                  ((bool)(knx.paramByte(LOG_UserFormula5Active) & LOG_UserFormula5ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula6                        (knx.paramData(LOG_UserFormula6))
// Benutzerformel 6 aktiv
#define ParamLOG_UserFormula6Active                  ((bool)(knx.paramByte(LOG_UserFormula6Active) & LOG_UserFormula6ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula7                        (knx.paramData(LOG_UserFormula7))
// Benutzerformel 7 aktiv
#define ParamLOG_UserFormula7Active                  ((bool)(knx.paramByte(LOG_UserFormula7Active) & LOG_UserFormula7ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula8                        (knx.paramData(LOG_UserFormula8))
// Benutzerformel 8 aktiv
#define ParamLOG_UserFormula8Active                  ((bool)(knx.paramByte(LOG_UserFormula8Active) & LOG_UserFormula8ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula9                        (knx.paramData(LOG_UserFormula9))
// Benutzerformel 9 aktiv
#define ParamLOG_UserFormula9Active                  ((bool)(knx.paramByte(LOG_UserFormula9Active) & LOG_UserFormula9ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula10                       (knx.paramData(LOG_UserFormula10))
// Benutzerformel 10 aktiv
#define ParamLOG_UserFormula10Active                 ((bool)(knx.paramByte(LOG_UserFormula10Active) & LOG_UserFormula10ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula11                       (knx.paramData(LOG_UserFormula11))
// Benutzerformel 11 aktiv
#define ParamLOG_UserFormula11Active                 ((bool)(knx.paramByte(LOG_UserFormula11Active) & LOG_UserFormula11ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula12                       (knx.paramData(LOG_UserFormula12))
// Benutzerformel 12 aktiv
#define ParamLOG_UserFormula12Active                 ((bool)(knx.paramByte(LOG_UserFormula12Active) & LOG_UserFormula12ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula13                       (knx.paramData(LOG_UserFormula13))
// Benutzerformel 13 aktiv
#define ParamLOG_UserFormula13Active                 ((bool)(knx.paramByte(LOG_UserFormula13Active) & LOG_UserFormula13ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula14                       (knx.paramData(LOG_UserFormula14))
// Benutzerformel 14 aktiv
#define ParamLOG_UserFormula14Active                 ((bool)(knx.paramByte(LOG_UserFormula14Active) & LOG_UserFormula14ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula15                       (knx.paramData(LOG_UserFormula15))
// Benutzerformel 15 aktiv
#define ParamLOG_UserFormula15Active                 ((bool)(knx.paramByte(LOG_UserFormula15Active) & LOG_UserFormula15ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula16                       (knx.paramData(LOG_UserFormula16))
// Benutzerformel 16 aktiv
#define ParamLOG_UserFormula16Active                 ((bool)(knx.paramByte(LOG_UserFormula16Active) & LOG_UserFormula16ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula17                       (knx.paramData(LOG_UserFormula17))
// Benutzerformel 17 aktiv
#define ParamLOG_UserFormula17Active                 ((bool)(knx.paramByte(LOG_UserFormula17Active) & LOG_UserFormula17ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula18                       (knx.paramData(LOG_UserFormula18))
// Benutzerformel 18 aktiv
#define ParamLOG_UserFormula18Active                 ((bool)(knx.paramByte(LOG_UserFormula18Active) & LOG_UserFormula18ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula19                       (knx.paramData(LOG_UserFormula19))
// Benutzerformel 19 aktiv
#define ParamLOG_UserFormula19Active                 ((bool)(knx.paramByte(LOG_UserFormula19Active) & LOG_UserFormula19ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula20                       (knx.paramData(LOG_UserFormula20))
// Benutzerformel 20 aktiv
#define ParamLOG_UserFormula20Active                 ((bool)(knx.paramByte(LOG_UserFormula20Active) & LOG_UserFormula20ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula21                       (knx.paramData(LOG_UserFormula21))
// Benutzerformel 21 aktiv
#define ParamLOG_UserFormula21Active                 ((bool)(knx.paramByte(LOG_UserFormula21Active) & LOG_UserFormula21ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula22                       (knx.paramData(LOG_UserFormula22))
// Benutzerformel 22 aktiv
#define ParamLOG_UserFormula22Active                 ((bool)(knx.paramByte(LOG_UserFormula22Active) & LOG_UserFormula22ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula23                       (knx.paramData(LOG_UserFormula23))
// Benutzerformel 23 aktiv
#define ParamLOG_UserFormula23Active                 ((bool)(knx.paramByte(LOG_UserFormula23Active) & LOG_UserFormula23ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula24                       (knx.paramData(LOG_UserFormula24))
// Benutzerformel 24 aktiv
#define ParamLOG_UserFormula24Active                 ((bool)(knx.paramByte(LOG_UserFormula24Active) & LOG_UserFormula24ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula25                       (knx.paramData(LOG_UserFormula25))
// Benutzerformel 25 aktiv
#define ParamLOG_UserFormula25Active                 ((bool)(knx.paramByte(LOG_UserFormula25Active) & LOG_UserFormula25ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula26                       (knx.paramData(LOG_UserFormula26))
// Benutzerformel 26 aktiv
#define ParamLOG_UserFormula26Active                 ((bool)(knx.paramByte(LOG_UserFormula26Active) & LOG_UserFormula26ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula27                       (knx.paramData(LOG_UserFormula27))
// Benutzerformel 27 aktiv
#define ParamLOG_UserFormula27Active                 ((bool)(knx.paramByte(LOG_UserFormula27Active) & LOG_UserFormula27ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula28                       (knx.paramData(LOG_UserFormula28))
// Benutzerformel 28 aktiv
#define ParamLOG_UserFormula28Active                 ((bool)(knx.paramByte(LOG_UserFormula28Active) & LOG_UserFormula28ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula29                       (knx.paramData(LOG_UserFormula29))
// Benutzerformel 29 aktiv
#define ParamLOG_UserFormula29Active                 ((bool)(knx.paramByte(LOG_UserFormula29Active) & LOG_UserFormula29ActiveMask))
// Formeldefinition
#define ParamLOG_UserFormula30                       (knx.paramData(LOG_UserFormula30))
// Benutzerformel 30 aktiv
#define ParamLOG_UserFormula30Active                 ((bool)(knx.paramByte(LOG_UserFormula30Active) & LOG_UserFormula30ActiveMask))

#define LOG_KoVacation 4
#define LOG_KoHoliday1 5
#define LOG_KoHoliday2 6
#define LOG_KoLedLock 8
#define LOG_KoBuzzerLock 9

// Urlaub
#define KoLOG_Vacation                            (knx.getGroupObject(LOG_KoVacation))
// Welcher Feiertag ist heute?
#define KoLOG_Holiday1                            (knx.getGroupObject(LOG_KoHoliday1))
// Welcher Feiertag ist morgen?
#define KoLOG_Holiday2                            (knx.getGroupObject(LOG_KoHoliday2))
// LED sperren
#define KoLOG_LedLock                             (knx.getGroupObject(LOG_KoLedLock))
// Buzzer sperren
#define KoLOG_BuzzerLock                          (knx.getGroupObject(LOG_KoBuzzerLock))

#define LOG_ChannelCount 50

// Parameter per channel
#define LOG_ParamBlockOffset 8956
#define LOG_ParamBlockSize 85
#define LOG_ParamCalcIndex(index) (index + LOG_ParamBlockOffset + _channelIndex * LOG_ParamBlockSize)

#define LOG_fChannelDelayBase                    0      // 2 Bits, Bit 7-6
#define     LOG_fChannelDelayBaseMask 0xC0
#define     LOG_fChannelDelayBaseShift 6
#define LOG_fChannelDelayTime                    0      // 14 Bits, Bit 13-0
#define     LOG_fChannelDelayTimeMask 0x3FFF
#define     LOG_fChannelDelayTimeShift 0
#define LOG_fLogic                               2      // 8 Bits, Bit 7-0
#define LOG_fCalculate                           3      // 2 Bits, Bit 1-0
#define     LOG_fCalculateMask 0x03
#define     LOG_fCalculateShift 0
#define LOG_fDisable                             3      // 1 Bit, Bit 2
#define     LOG_fDisableMask 0x04
#define     LOG_fDisableShift 2
#define LOG_fAlarm                               3      // 1 Bit, Bit 3
#define     LOG_fAlarmMask 0x08
#define     LOG_fAlarmShift 3
#define LOG_fTGate                               3      // 1 Bit, Bit 4
#define     LOG_fTGateMask 0x10
#define     LOG_fTGateShift 4
#define LOG_fOInternalOn                         3      // 1 Bit, Bit 5
#define     LOG_fOInternalOnMask 0x20
#define     LOG_fOInternalOnShift 5
#define LOG_fOInternalOff                        3      // 1 Bit, Bit 6
#define     LOG_fOInternalOffMask 0x40
#define     LOG_fOInternalOffShift 6
#define LOG_fTrigger                             4      // 8 Bits, Bit 7-0
#define LOG_fTriggerE1                           4      // 1 Bit, Bit 0
#define     LOG_fTriggerE1Mask 0x01
#define     LOG_fTriggerE1Shift 0
#define LOG_fTriggerE2                           4      // 1 Bit, Bit 1
#define     LOG_fTriggerE2Mask 0x02
#define     LOG_fTriggerE2Shift 1
#define LOG_fTriggerI1                           4      // 1 Bit, Bit 2
#define     LOG_fTriggerI1Mask 0x04
#define     LOG_fTriggerI1Shift 2
#define LOG_fTriggerI2                           4      // 1 Bit, Bit 3
#define     LOG_fTriggerI2Mask 0x08
#define     LOG_fTriggerI2Shift 3
#define LOG_fTriggerTime                         4      // 8 Bits, Bit 7-0
#define LOG_fTriggerGateClose                    5      // 2 Bits, Bit 7-6
#define     LOG_fTriggerGateCloseMask 0xC0
#define     LOG_fTriggerGateCloseShift 6
#define LOG_fTriggerGateOpen                     5      // 2 Bits, Bit 5-4
#define     LOG_fTriggerGateOpenMask 0x30
#define     LOG_fTriggerGateOpenShift 4
#define LOG_fE1ConvertInt                        6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertIntMask 0xF0
#define     LOG_fE1ConvertIntShift 4
#define LOG_fE1Convert                           6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertMask 0xF0
#define     LOG_fE1ConvertShift 4
#define LOG_fE1ConvertFloat                      6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertFloatMask 0xF0
#define     LOG_fE1ConvertFloatShift 4
#define LOG_fE1ConvertSpecial                    6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertSpecialMask 0xF0
#define     LOG_fE1ConvertSpecialShift 4
#define LOG_fE1ConvertBool                       6      // 4 Bits, Bit 7-4
#define     LOG_fE1ConvertBoolMask 0xF0
#define     LOG_fE1ConvertBoolShift 4
#define LOG_fE1                                  6      // 2 Bits, Bit 1-0
#define     LOG_fE1Mask 0x03
#define     LOG_fE1Shift 0
#define LOG_fE1Dpt                               7      // 8 Bits, Bit 7-0
#define LOG_fE1RepeatBase                        8      // 2 Bits, Bit 7-6
#define     LOG_fE1RepeatBaseMask 0xC0
#define     LOG_fE1RepeatBaseShift 6
#define LOG_fE1RepeatTime                        8      // 14 Bits, Bit 13-0
#define     LOG_fE1RepeatTimeMask 0x3FFF
#define     LOG_fE1RepeatTimeShift 0
#define LOG_fE1OtherKO                          10      // uint16_t
#define LOG_fE1OtherKORel                       10      // int16_t
#define LOG_fE1Default                          12      // 2 Bits, Bit 1-0
#define     LOG_fE1DefaultMask 0x03
#define     LOG_fE1DefaultShift 0
#define LOG_fE1DefaultExt                       12      // 2 Bits, Bit 1-0
#define     LOG_fE1DefaultExtMask 0x03
#define     LOG_fE1DefaultExtShift 0
#define LOG_fE1DefaultEEPROM                    12      // 1 Bit, Bit 2
#define     LOG_fE1DefaultEEPROMMask 0x04
#define     LOG_fE1DefaultEEPROMShift 2
#define LOG_fE1DefaultRepeat                    12      // 1 Bit, Bit 3
#define     LOG_fE1DefaultRepeatMask 0x08
#define     LOG_fE1DefaultRepeatShift 3
#define LOG_fE1UseOtherKO                       12      // 2 Bits, Bit 5-4
#define     LOG_fE1UseOtherKOMask 0x30
#define     LOG_fE1UseOtherKOShift 4
#define LOG_fE1LowDelta                         13      // int32_t
#define LOG_fE1HighDelta                        17      // int32_t
#define LOG_fE1LowDeltaFloat                    13      // float
#define LOG_fE1HighDeltaFloat                   17      // float
#define LOG_fE1LowDeltaDouble                   13      // float
#define LOG_fE1HighDeltaDouble                  17      // float
#define LOG_fE1Low0Valid                        20      // 1 Bit, Bit 7
#define     LOG_fE1Low0ValidMask 0x80
#define     LOG_fE1Low0ValidShift 7
#define LOG_fE1Low1Valid                        20      // 1 Bit, Bit 6
#define     LOG_fE1Low1ValidMask 0x40
#define     LOG_fE1Low1ValidShift 6
#define LOG_fE1Low2Valid                        20      // 1 Bit, Bit 5
#define     LOG_fE1Low2ValidMask 0x20
#define     LOG_fE1Low2ValidShift 5
#define LOG_fE1Low3Valid                        20      // 1 Bit, Bit 4
#define     LOG_fE1Low3ValidMask 0x10
#define     LOG_fE1Low3ValidShift 4
#define LOG_fE1Low4Valid                        20      // 1 Bit, Bit 3
#define     LOG_fE1Low4ValidMask 0x08
#define     LOG_fE1Low4ValidShift 3
#define LOG_fE1Low5Valid                        20      // 1 Bit, Bit 2
#define     LOG_fE1Low5ValidMask 0x04
#define     LOG_fE1Low5ValidShift 2
#define LOG_fE1Low6Valid                        20      // 1 Bit, Bit 1
#define     LOG_fE1Low6ValidMask 0x02
#define     LOG_fE1Low6ValidShift 1
#define LOG_fE1Low0Dpt2                         13      // 8 Bits, Bit 7-0
#define LOG_fE1Low1Dpt2                         14      // 8 Bits, Bit 7-0
#define LOG_fE1Low2Dpt2                         15      // 8 Bits, Bit 7-0
#define LOG_fE1Low3Dpt2                         16      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt2Fix                       13      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt5                          13      // uint8_t
#define LOG_fE1HighDpt5                         17      // uint8_t
#define LOG_fE1Low0Dpt5In                       13      // uint8_t
#define LOG_fE1Low1Dpt5In                       14      // uint8_t
#define LOG_fE1Low2Dpt5In                       15      // uint8_t
#define LOG_fE1Low3Dpt5In                       16      // uint8_t
#define LOG_fE1Low4Dpt5In                       17      // uint8_t
#define LOG_fE1Low5Dpt5In                       18      // uint8_t
#define LOG_fE1Low6Dpt5In                       19      // uint8_t
#define LOG_fE1LowDpt5Fix                       13      // uint8_t
#define LOG_fE1LowDpt5001                       13      // uint8_t
#define LOG_fE1HighDpt5001                      17      // uint8_t
#define LOG_fE1Low0Dpt5xIn                      13      // uint8_t
#define LOG_fE1Low1Dpt5xIn                      14      // uint8_t
#define LOG_fE1Low2Dpt5xIn                      15      // uint8_t
#define LOG_fE1Low3Dpt5xIn                      16      // uint8_t
#define LOG_fE1Low4Dpt5xIn                      17      // uint8_t
#define LOG_fE1Low5Dpt5xIn                      18      // uint8_t
#define LOG_fE1Low6Dpt5xIn                      19      // uint8_t
#define LOG_fE1LowDpt5xFix                      13      // uint8_t
#define LOG_fE1LowDpt6                          13      // int8_t
#define LOG_fE1HighDpt6                         17      // int8_t
#define LOG_fE1Low0Dpt6In                       13      // int8_t
#define LOG_fE1Low1Dpt6In                       14      // int8_t
#define LOG_fE1Low2Dpt6In                       15      // int8_t
#define LOG_fE1Low3Dpt6In                       16      // int8_t
#define LOG_fE1Low4Dpt6In                       17      // int8_t
#define LOG_fE1Low5Dpt6In                       18      // int8_t
#define LOG_fE1Low6Dpt6In                       19      // int8_t
#define LOG_fE1LowDpt6Fix                       13      // int8_t
#define LOG_fE1LowDpt7                          13      // uint16_t
#define LOG_fE1HighDpt7                         17      // uint16_t
#define LOG_fE1Low0Dpt7In                       13      // uint16_t
#define LOG_fE1Low1Dpt7In                       15      // uint16_t
#define LOG_fE1Low2Dpt7In                       17      // uint16_t
#define LOG_fE1LowDpt7Fix                       13      // uint16_t
#define LOG_fE1LowDpt8                          13      // int16_t
#define LOG_fE1HighDpt8                         17      // int16_t
#define LOG_fE1Low0Dpt8In                       13      // int16_t
#define LOG_fE1Low1Dpt8In                       15      // int16_t
#define LOG_fE1Low2Dpt8In                       17      // int16_t
#define LOG_fE1LowDpt8Fix                       13      // int16_t
#define LOG_fE1LowDpt9                          13      // float
#define LOG_fE1HighDpt9                         17      // float
#define LOG_fE1LowDpt9Fix                       13      // float
#define LOG_fE1LowDpt12                         13      // uint32_t
#define LOG_fE1HighDpt12                        17      // uint32_t
#define LOG_fE1LowDpt12Fix                      13      // uint32_t
#define LOG_fE1LowDpt13                         13      // int32_t
#define LOG_fE1HighDpt13                        17      // int32_t
#define LOG_fE1LowDpt13Fix                      13      // int32_t
#define LOG_fE1LowDpt14                         13      // float
#define LOG_fE1HighDpt14                        17      // float
#define LOG_fE1LowDpt14Fix                      13      // float
#define LOG_fE1Low0Dpt17                        13      // 8 Bits, Bit 7-0
#define LOG_fE1Low1Dpt17                        14      // 8 Bits, Bit 7-0
#define LOG_fE1Low2Dpt17                        15      // 8 Bits, Bit 7-0
#define LOG_fE1Low3Dpt17                        16      // 8 Bits, Bit 7-0
#define LOG_fE1Low4Dpt17                        17      // 8 Bits, Bit 7-0
#define LOG_fE1Low5Dpt17                        18      // 8 Bits, Bit 7-0
#define LOG_fE1Low6Dpt17                        19      // 8 Bits, Bit 7-0
#define LOG_fE1Low7Dpt17                        20      // 8 Bits, Bit 7-0
#define LOG_fE1LowDpt17Fix                      13      // 8 Bits, Bit 7-0
#define LOG_fE1LowDptRGB                        13      // int32_t
#define LOG_fE1HighDptRGB                       17      // int32_t
#define LOG_fE1LowDptRGBFix                     13      // int32_t
#define LOG_fE2ConvertInt                       21      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertIntMask 0xF0
#define     LOG_fE2ConvertIntShift 4
#define LOG_fE2Convert                          21      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertMask 0xF0
#define     LOG_fE2ConvertShift 4
#define LOG_fE2ConvertFloat                     21      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertFloatMask 0xF0
#define     LOG_fE2ConvertFloatShift 4
#define LOG_fE2ConvertSpecial                   21      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertSpecialMask 0xF0
#define     LOG_fE2ConvertSpecialShift 4
#define LOG_fE2ConvertBool                      21      // 4 Bits, Bit 7-4
#define     LOG_fE2ConvertBoolMask 0xF0
#define     LOG_fE2ConvertBoolShift 4
#define LOG_fE2                                 21      // 2 Bits, Bit 1-0
#define     LOG_fE2Mask 0x03
#define     LOG_fE2Shift 0
#define LOG_fE2Dpt                              22      // 8 Bits, Bit 7-0
#define LOG_fE2RepeatBase                       23      // 2 Bits, Bit 7-6
#define     LOG_fE2RepeatBaseMask 0xC0
#define     LOG_fE2RepeatBaseShift 6
#define LOG_fE2RepeatTime                       23      // 14 Bits, Bit 13-0
#define     LOG_fE2RepeatTimeMask 0x3FFF
#define     LOG_fE2RepeatTimeShift 0
#define LOG_fE2OtherKO                          25      // uint16_t
#define LOG_fE2OtherKORel                       25      // int16_t
#define LOG_fE2Default                          27      // 2 Bits, Bit 1-0
#define     LOG_fE2DefaultMask 0x03
#define     LOG_fE2DefaultShift 0
#define LOG_fE2DefaultExt                       27      // 2 Bits, Bit 1-0
#define     LOG_fE2DefaultExtMask 0x03
#define     LOG_fE2DefaultExtShift 0
#define LOG_fE2DefaultEEPROM                    27      // 1 Bit, Bit 2
#define     LOG_fE2DefaultEEPROMMask 0x04
#define     LOG_fE2DefaultEEPROMShift 2
#define LOG_fE2DefaultRepeat                    27      // 1 Bit, Bit 3
#define     LOG_fE2DefaultRepeatMask 0x08
#define     LOG_fE2DefaultRepeatShift 3
#define LOG_fE2UseOtherKO                       27      // 2 Bits, Bit 5-4
#define     LOG_fE2UseOtherKOMask 0x30
#define     LOG_fE2UseOtherKOShift 4
#define LOG_fE2LowDelta                         28      // int32_t
#define LOG_fE2HighDelta                        32      // int32_t
#define LOG_fE2LowDeltaFloat                    28      // float
#define LOG_fE2HighDeltaFloat                   32      // float
#define LOG_fE2LowDeltaDouble                   28      // float
#define LOG_fE2HighDeltaDouble                  32      // float
#define LOG_fE2Low0Valid                        35      // 1 Bit, Bit 7
#define     LOG_fE2Low0ValidMask 0x80
#define     LOG_fE2Low0ValidShift 7
#define LOG_fE2Low1Valid                        35      // 1 Bit, Bit 6
#define     LOG_fE2Low1ValidMask 0x40
#define     LOG_fE2Low1ValidShift 6
#define LOG_fE2Low2Valid                        35      // 1 Bit, Bit 5
#define     LOG_fE2Low2ValidMask 0x20
#define     LOG_fE2Low2ValidShift 5
#define LOG_fE2Low3Valid                        35      // 1 Bit, Bit 4
#define     LOG_fE2Low3ValidMask 0x10
#define     LOG_fE2Low3ValidShift 4
#define LOG_fE2Low4Valid                        35      // 1 Bit, Bit 3
#define     LOG_fE2Low4ValidMask 0x08
#define     LOG_fE2Low4ValidShift 3
#define LOG_fE2Low5Valid                        35      // 1 Bit, Bit 2
#define     LOG_fE2Low5ValidMask 0x04
#define     LOG_fE2Low5ValidShift 2
#define LOG_fE2Low6Valid                        35      // 1 Bit, Bit 1
#define     LOG_fE2Low6ValidMask 0x02
#define     LOG_fE2Low6ValidShift 1
#define LOG_fE2Low0Dpt2                         28      // 8 Bits, Bit 7-0
#define LOG_fE2Low1Dpt2                         29      // 8 Bits, Bit 7-0
#define LOG_fE2Low2Dpt2                         30      // 8 Bits, Bit 7-0
#define LOG_fE2Low3Dpt2                         31      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt2Fix                       28      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt5                          28      // uint8_t
#define LOG_fE2HighDpt5                         32      // uint8_t
#define LOG_fE2Low0Dpt5In                       28      // uint8_t
#define LOG_fE2Low1Dpt5In                       29      // uint8_t
#define LOG_fE2Low2Dpt5In                       30      // uint8_t
#define LOG_fE2Low3Dpt5In                       31      // uint8_t
#define LOG_fE2Low4Dpt5In                       32      // uint8_t
#define LOG_fE2Low5Dpt5In                       33      // uint8_t
#define LOG_fE2Low6Dpt5In                       34      // uint8_t
#define LOG_fE2LowDpt5Fix                       28      // uint8_t
#define LOG_fE2LowDpt5001                       28      // uint8_t
#define LOG_fE2HighDpt5001                      32      // uint8_t
#define LOG_fE2Low0Dpt5xIn                      28      // uint8_t
#define LOG_fE2Low1Dpt5xIn                      29      // uint8_t
#define LOG_fE2Low2Dpt5xIn                      30      // uint8_t
#define LOG_fE2Low3Dpt5xIn                      31      // uint8_t
#define LOG_fE2Low4Dpt5xIn                      32      // uint8_t
#define LOG_fE2Low5Dpt5xIn                      33      // uint8_t
#define LOG_fE2Low6Dpt5xIn                      34      // uint8_t
#define LOG_fE2LowDpt5xFix                      28      // uint8_t
#define LOG_fE2LowDpt6                          28      // int8_t
#define LOG_fE2HighDpt6                         32      // int8_t
#define LOG_fE2Low0Dpt6In                       28      // int8_t
#define LOG_fE2Low1Dpt6In                       29      // int8_t
#define LOG_fE2Low2Dpt6In                       30      // int8_t
#define LOG_fE2Low3Dpt6In                       31      // int8_t
#define LOG_fE2Low4Dpt6In                       32      // int8_t
#define LOG_fE2Low5Dpt6In                       33      // int8_t
#define LOG_fE2Low6Dpt6In                       34      // int8_t
#define LOG_fE2LowDpt6Fix                       28      // int8_t
#define LOG_fE2LowDpt7                          28      // uint16_t
#define LOG_fE2HighDpt7                         32      // uint16_t
#define LOG_fE2Low0Dpt7In                       28      // uint16_t
#define LOG_fE2Low1Dpt7In                       30      // uint16_t
#define LOG_fE2Low2Dpt7In                       32      // uint16_t
#define LOG_fE2LowDpt7Fix                       28      // uint16_t
#define LOG_fE2LowDpt8                          28      // int16_t
#define LOG_fE2HighDpt8                         32      // int16_t
#define LOG_fE2Low0Dpt8In                       28      // int16_t
#define LOG_fE2Low1Dpt8In                       30      // int16_t
#define LOG_fE2Low2Dpt8In                       32      // int16_t
#define LOG_fE2LowDpt8Fix                       28      // int16_t
#define LOG_fE2LowDpt9                          28      // float
#define LOG_fE2HighDpt9                         32      // float
#define LOG_fE2LowDpt9Fix                       28      // float
#define LOG_fE2LowDpt12                         28      // uint32_t
#define LOG_fE2HighDpt12                        32      // uint32_t
#define LOG_fE2LowDpt12Fix                      28      // uint32_t
#define LOG_fE2LowDpt13                         28      // int32_t
#define LOG_fE2HighDpt13                        32      // int32_t
#define LOG_fE2LowDpt13Fix                      28      // int32_t
#define LOG_fE2LowDpt14                         28      // float
#define LOG_fE2HighDpt14                        32      // float
#define LOG_fE2LowDpt14Fix                      28      // float
#define LOG_fE2Low0Dpt17                        28      // 8 Bits, Bit 7-0
#define LOG_fE2Low1Dpt17                        29      // 8 Bits, Bit 7-0
#define LOG_fE2Low2Dpt17                        30      // 8 Bits, Bit 7-0
#define LOG_fE2Low3Dpt17                        31      // 8 Bits, Bit 7-0
#define LOG_fE2Low4Dpt17                        32      // 8 Bits, Bit 7-0
#define LOG_fE2Low5Dpt17                        33      // 8 Bits, Bit 7-0
#define LOG_fE2Low6Dpt17                        34      // 8 Bits, Bit 7-0
#define LOG_fE2Low7Dpt17                        35      // 8 Bits, Bit 7-0
#define LOG_fE2LowDpt17Fix                      28      // 8 Bits, Bit 7-0
#define LOG_fE2LowDptRGB                        28      // int32_t
#define LOG_fE2HighDptRGB                       32      // int32_t
#define LOG_fE2LowDptRGBFix                     28      // int32_t
#define LOG_fTd1DuskDawn                         6      // 4 Bits, Bit 7-4
#define     LOG_fTd1DuskDawnMask 0xF0
#define     LOG_fTd1DuskDawnShift 4
#define LOG_fTd2DuskDawn                         6      // 4 Bits, Bit 3-0
#define     LOG_fTd2DuskDawnMask 0x0F
#define     LOG_fTd2DuskDawnShift 0
#define LOG_fTd3DuskDawn                         7      // 4 Bits, Bit 7-4
#define     LOG_fTd3DuskDawnMask 0xF0
#define     LOG_fTd3DuskDawnShift 4
#define LOG_fTd4DuskDawn                         7      // 4 Bits, Bit 3-0
#define     LOG_fTd4DuskDawnMask 0x0F
#define     LOG_fTd4DuskDawnShift 0
#define LOG_fTd5DuskDawn                         8      // 4 Bits, Bit 7-4
#define     LOG_fTd5DuskDawnMask 0xF0
#define     LOG_fTd5DuskDawnShift 4
#define LOG_fTd6DuskDawn                         8      // 4 Bits, Bit 3-0
#define     LOG_fTd6DuskDawnMask 0x0F
#define     LOG_fTd6DuskDawnShift 0
#define LOG_fTd7DuskDawn                         9      // 4 Bits, Bit 7-4
#define     LOG_fTd7DuskDawnMask 0xF0
#define     LOG_fTd7DuskDawnShift 4
#define LOG_fTd8DuskDawn                         9      // 4 Bits, Bit 3-0
#define     LOG_fTd8DuskDawnMask 0x0F
#define     LOG_fTd8DuskDawnShift 0
#define LOG_fTYearDay                           10      // 2 Bits, Bit 7-6
#define     LOG_fTYearDayMask 0xC0
#define     LOG_fTYearDayShift 6
#define LOG_fTHoliday                           10      // 2 Bits, Bit 5-4
#define     LOG_fTHolidayMask 0x30
#define     LOG_fTHolidayShift 4
#define LOG_fTRestoreState                      10      // 2 Bits, Bit 3-2
#define     LOG_fTRestoreStateMask 0x0C
#define     LOG_fTRestoreStateShift 2
#define LOG_fTVacation                          10      // 2 Bits, Bit 1-0
#define     LOG_fTVacationMask 0x03
#define     LOG_fTVacationShift 0
#define LOG_fTd1ValueNum                        11      // uint8_t
#define LOG_fTd2ValueNum                        12      // uint8_t
#define LOG_fTd3ValueNum                        13      // uint8_t
#define LOG_fTd4ValueNum                        14      // uint8_t
#define LOG_fTd5ValueNum                        15      // uint8_t
#define LOG_fTd6ValueNum                        16      // uint8_t
#define LOG_fTd7ValueNum                        17      // uint8_t
#define LOG_fTd8ValueNum                        18      // uint8_t
#define LOG_fTd1Value                           20      // 1 Bit, Bit 7
#define     LOG_fTd1ValueMask 0x80
#define     LOG_fTd1ValueShift 7
#define LOG_fTd1Degree                          20      // 6 Bits, Bit 6-1
#define     LOG_fTd1DegreeMask 0x7E
#define     LOG_fTd1DegreeShift 1
#define LOG_fTd1HourAbs                         20      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourAbsMask 0x3E
#define     LOG_fTd1HourAbsShift 1
#define LOG_fTd1HourRel                         20      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourRelMask 0x3E
#define     LOG_fTd1HourRelShift 1
#define LOG_fTd1HourRelShort                    20      // 5 Bits, Bit 5-1
#define     LOG_fTd1HourRelShortMask 0x3E
#define     LOG_fTd1HourRelShortShift 1
#define LOG_fTd1MinuteAbs                       20      // 6 Bits, Bit 0--5
#define LOG_fTd1MinuteRel                       20      // 6 Bits, Bit 0--5
#define LOG_fTd1Weekday                         21      // 3 Bits, Bit 2-0
#define     LOG_fTd1WeekdayMask 0x07
#define     LOG_fTd1WeekdayShift 0
#define LOG_fTd2Value                           22      // 1 Bit, Bit 7
#define     LOG_fTd2ValueMask 0x80
#define     LOG_fTd2ValueShift 7
#define LOG_fTd2Degree                          22      // 6 Bits, Bit 6-1
#define     LOG_fTd2DegreeMask 0x7E
#define     LOG_fTd2DegreeShift 1
#define LOG_fTd2HourAbs                         22      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourAbsMask 0x3E
#define     LOG_fTd2HourAbsShift 1
#define LOG_fTd2HourRel                         22      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourRelMask 0x3E
#define     LOG_fTd2HourRelShift 1
#define LOG_fTd2HourRelShort                    22      // 5 Bits, Bit 5-1
#define     LOG_fTd2HourRelShortMask 0x3E
#define     LOG_fTd2HourRelShortShift 1
#define LOG_fTd2MinuteAbs                       22      // 6 Bits, Bit 0--5
#define LOG_fTd2MinuteRel                       22      // 6 Bits, Bit 0--5
#define LOG_fTd2Weekday                         23      // 3 Bits, Bit 2-0
#define     LOG_fTd2WeekdayMask 0x07
#define     LOG_fTd2WeekdayShift 0
#define LOG_fTd3Value                           24      // 1 Bit, Bit 7
#define     LOG_fTd3ValueMask 0x80
#define     LOG_fTd3ValueShift 7
#define LOG_fTd3Degree                          24      // 6 Bits, Bit 6-1
#define     LOG_fTd3DegreeMask 0x7E
#define     LOG_fTd3DegreeShift 1
#define LOG_fTd3HourAbs                         24      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourAbsMask 0x3E
#define     LOG_fTd3HourAbsShift 1
#define LOG_fTd3HourRel                         24      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourRelMask 0x3E
#define     LOG_fTd3HourRelShift 1
#define LOG_fTd3HourRelShort                    24      // 5 Bits, Bit 5-1
#define     LOG_fTd3HourRelShortMask 0x3E
#define     LOG_fTd3HourRelShortShift 1
#define LOG_fTd3MinuteAbs                       24      // 6 Bits, Bit 0--5
#define LOG_fTd3MinuteRel                       24      // 6 Bits, Bit 0--5
#define LOG_fTd3Weekday                         25      // 3 Bits, Bit 2-0
#define     LOG_fTd3WeekdayMask 0x07
#define     LOG_fTd3WeekdayShift 0
#define LOG_fTd4Value                           26      // 1 Bit, Bit 7
#define     LOG_fTd4ValueMask 0x80
#define     LOG_fTd4ValueShift 7
#define LOG_fTd4Degree                          26      // 6 Bits, Bit 6-1
#define     LOG_fTd4DegreeMask 0x7E
#define     LOG_fTd4DegreeShift 1
#define LOG_fTd4HourAbs                         26      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourAbsMask 0x3E
#define     LOG_fTd4HourAbsShift 1
#define LOG_fTd4HourRel                         26      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourRelMask 0x3E
#define     LOG_fTd4HourRelShift 1
#define LOG_fTd4HourRelShort                    26      // 5 Bits, Bit 5-1
#define     LOG_fTd4HourRelShortMask 0x3E
#define     LOG_fTd4HourRelShortShift 1
#define LOG_fTd4MinuteAbs                       26      // 6 Bits, Bit 0--5
#define LOG_fTd4MinuteRel                       26      // 6 Bits, Bit 0--5
#define LOG_fTd4Weekday                         27      // 3 Bits, Bit 2-0
#define     LOG_fTd4WeekdayMask 0x07
#define     LOG_fTd4WeekdayShift 0
#define LOG_fTd5Value                           28      // 1 Bit, Bit 7
#define     LOG_fTd5ValueMask 0x80
#define     LOG_fTd5ValueShift 7
#define LOG_fTd5Degree                          28      // 6 Bits, Bit 6-1
#define     LOG_fTd5DegreeMask 0x7E
#define     LOG_fTd5DegreeShift 1
#define LOG_fTd5HourAbs                         28      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourAbsMask 0x3E
#define     LOG_fTd5HourAbsShift 1
#define LOG_fTd5HourRel                         28      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourRelMask 0x3E
#define     LOG_fTd5HourRelShift 1
#define LOG_fTd5HourRelShort                    28      // 5 Bits, Bit 5-1
#define     LOG_fTd5HourRelShortMask 0x3E
#define     LOG_fTd5HourRelShortShift 1
#define LOG_fTd5MinuteAbs                       28      // 6 Bits, Bit 0--5
#define LOG_fTd5MinuteRel                       28      // 6 Bits, Bit 0--5
#define LOG_fTd5Weekday                         29      // 3 Bits, Bit 2-0
#define     LOG_fTd5WeekdayMask 0x07
#define     LOG_fTd5WeekdayShift 0
#define LOG_fTd6Value                           30      // 1 Bit, Bit 7
#define     LOG_fTd6ValueMask 0x80
#define     LOG_fTd6ValueShift 7
#define LOG_fTd6Degree                          30      // 6 Bits, Bit 6-1
#define     LOG_fTd6DegreeMask 0x7E
#define     LOG_fTd6DegreeShift 1
#define LOG_fTd6HourAbs                         30      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourAbsMask 0x3E
#define     LOG_fTd6HourAbsShift 1
#define LOG_fTd6HourRel                         30      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourRelMask 0x3E
#define     LOG_fTd6HourRelShift 1
#define LOG_fTd6HourRelShort                    30      // 5 Bits, Bit 5-1
#define     LOG_fTd6HourRelShortMask 0x3E
#define     LOG_fTd6HourRelShortShift 1
#define LOG_fTd6MinuteAbs                       30      // 6 Bits, Bit 0--5
#define LOG_fTd6MinuteRel                       30      // 6 Bits, Bit 0--5
#define LOG_fTd6Weekday                         31      // 3 Bits, Bit 2-0
#define     LOG_fTd6WeekdayMask 0x07
#define     LOG_fTd6WeekdayShift 0
#define LOG_fTd7Value                           32      // 1 Bit, Bit 7
#define     LOG_fTd7ValueMask 0x80
#define     LOG_fTd7ValueShift 7
#define LOG_fTd7Degree                          32      // 6 Bits, Bit 6-1
#define     LOG_fTd7DegreeMask 0x7E
#define     LOG_fTd7DegreeShift 1
#define LOG_fTd7HourAbs                         32      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourAbsMask 0x3E
#define     LOG_fTd7HourAbsShift 1
#define LOG_fTd7HourRel                         32      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourRelMask 0x3E
#define     LOG_fTd7HourRelShift 1
#define LOG_fTd7HourRelShort                    32      // 5 Bits, Bit 5-1
#define     LOG_fTd7HourRelShortMask 0x3E
#define     LOG_fTd7HourRelShortShift 1
#define LOG_fTd7MinuteAbs                       32      // 6 Bits, Bit 0--5
#define LOG_fTd7MinuteRel                       32      // 6 Bits, Bit 0--5
#define LOG_fTd7Weekday                         33      // 3 Bits, Bit 2-0
#define     LOG_fTd7WeekdayMask 0x07
#define     LOG_fTd7WeekdayShift 0
#define LOG_fTd8Value                           34      // 1 Bit, Bit 7
#define     LOG_fTd8ValueMask 0x80
#define     LOG_fTd8ValueShift 7
#define LOG_fTd8Degree                          34      // 6 Bits, Bit 6-1
#define     LOG_fTd8DegreeMask 0x7E
#define     LOG_fTd8DegreeShift 1
#define LOG_fTd8HourAbs                         34      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourAbsMask 0x3E
#define     LOG_fTd8HourAbsShift 1
#define LOG_fTd8HourRel                         34      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourRelMask 0x3E
#define     LOG_fTd8HourRelShift 1
#define LOG_fTd8HourRelShort                    34      // 5 Bits, Bit 5-1
#define     LOG_fTd8HourRelShortMask 0x3E
#define     LOG_fTd8HourRelShortShift 1
#define LOG_fTd8MinuteAbs                       34      // 6 Bits, Bit 0--5
#define LOG_fTd8MinuteRel                       34      // 6 Bits, Bit 0--5
#define LOG_fTd8Weekday                         35      // 3 Bits, Bit 2-0
#define     LOG_fTd8WeekdayMask 0x07
#define     LOG_fTd8WeekdayShift 0
#define LOG_fTy1Weekday1                        28      // 1 Bit, Bit 7
#define     LOG_fTy1Weekday1Mask 0x80
#define     LOG_fTy1Weekday1Shift 7
#define LOG_fTy1Weekday2                        28      // 1 Bit, Bit 6
#define     LOG_fTy1Weekday2Mask 0x40
#define     LOG_fTy1Weekday2Shift 6
#define LOG_fTy1Weekday3                        28      // 1 Bit, Bit 5
#define     LOG_fTy1Weekday3Mask 0x20
#define     LOG_fTy1Weekday3Shift 5
#define LOG_fTy1Weekday4                        28      // 1 Bit, Bit 4
#define     LOG_fTy1Weekday4Mask 0x10
#define     LOG_fTy1Weekday4Shift 4
#define LOG_fTy1Weekday5                        28      // 1 Bit, Bit 3
#define     LOG_fTy1Weekday5Mask 0x08
#define     LOG_fTy1Weekday5Shift 3
#define LOG_fTy1Weekday6                        28      // 1 Bit, Bit 2
#define     LOG_fTy1Weekday6Mask 0x04
#define     LOG_fTy1Weekday6Shift 2
#define LOG_fTy1Weekday7                        28      // 1 Bit, Bit 1
#define     LOG_fTy1Weekday7Mask 0x02
#define     LOG_fTy1Weekday7Shift 1
#define LOG_fTy1Day                             28      // 7 Bits, Bit 7-1
#define     LOG_fTy1DayMask 0xFE
#define     LOG_fTy1DayShift 1
#define LOG_fTy1IsWeekday                       28      // 1 Bit, Bit 0
#define     LOG_fTy1IsWeekdayMask 0x01
#define     LOG_fTy1IsWeekdayShift 0
#define LOG_fTy1Month                           29      // 4 Bits, Bit 7-4
#define     LOG_fTy1MonthMask 0xF0
#define     LOG_fTy1MonthShift 4
#define LOG_fTy2Weekday1                        30      // 1 Bit, Bit 7
#define     LOG_fTy2Weekday1Mask 0x80
#define     LOG_fTy2Weekday1Shift 7
#define LOG_fTy2Weekday2                        30      // 1 Bit, Bit 6
#define     LOG_fTy2Weekday2Mask 0x40
#define     LOG_fTy2Weekday2Shift 6
#define LOG_fTy2Weekday3                        30      // 1 Bit, Bit 5
#define     LOG_fTy2Weekday3Mask 0x20
#define     LOG_fTy2Weekday3Shift 5
#define LOG_fTy2Weekday4                        30      // 1 Bit, Bit 4
#define     LOG_fTy2Weekday4Mask 0x10
#define     LOG_fTy2Weekday4Shift 4
#define LOG_fTy2Weekday5                        30      // 1 Bit, Bit 3
#define     LOG_fTy2Weekday5Mask 0x08
#define     LOG_fTy2Weekday5Shift 3
#define LOG_fTy2Weekday6                        30      // 1 Bit, Bit 2
#define     LOG_fTy2Weekday6Mask 0x04
#define     LOG_fTy2Weekday6Shift 2
#define LOG_fTy2Weekday7                        30      // 1 Bit, Bit 1
#define     LOG_fTy2Weekday7Mask 0x02
#define     LOG_fTy2Weekday7Shift 1
#define LOG_fTy2Day                             30      // 7 Bits, Bit 7-1
#define     LOG_fTy2DayMask 0xFE
#define     LOG_fTy2DayShift 1
#define LOG_fTy2IsWeekday                       30      // 1 Bit, Bit 0
#define     LOG_fTy2IsWeekdayMask 0x01
#define     LOG_fTy2IsWeekdayShift 0
#define LOG_fTy2Month                           31      // 4 Bits, Bit 7-4
#define     LOG_fTy2MonthMask 0xF0
#define     LOG_fTy2MonthShift 4
#define LOG_fTy3Weekday1                        32      // 1 Bit, Bit 7
#define     LOG_fTy3Weekday1Mask 0x80
#define     LOG_fTy3Weekday1Shift 7
#define LOG_fTy3Weekday2                        32      // 1 Bit, Bit 6
#define     LOG_fTy3Weekday2Mask 0x40
#define     LOG_fTy3Weekday2Shift 6
#define LOG_fTy3Weekday3                        32      // 1 Bit, Bit 5
#define     LOG_fTy3Weekday3Mask 0x20
#define     LOG_fTy3Weekday3Shift 5
#define LOG_fTy3Weekday4                        32      // 1 Bit, Bit 4
#define     LOG_fTy3Weekday4Mask 0x10
#define     LOG_fTy3Weekday4Shift 4
#define LOG_fTy3Weekday5                        32      // 1 Bit, Bit 3
#define     LOG_fTy3Weekday5Mask 0x08
#define     LOG_fTy3Weekday5Shift 3
#define LOG_fTy3Weekday6                        32      // 1 Bit, Bit 2
#define     LOG_fTy3Weekday6Mask 0x04
#define     LOG_fTy3Weekday6Shift 2
#define LOG_fTy3Weekday7                        32      // 1 Bit, Bit 1
#define     LOG_fTy3Weekday7Mask 0x02
#define     LOG_fTy3Weekday7Shift 1
#define LOG_fTy3Day                             32      // 7 Bits, Bit 7-1
#define     LOG_fTy3DayMask 0xFE
#define     LOG_fTy3DayShift 1
#define LOG_fTy3IsWeekday                       32      // 1 Bit, Bit 0
#define     LOG_fTy3IsWeekdayMask 0x01
#define     LOG_fTy3IsWeekdayShift 0
#define LOG_fTy3Month                           33      // 4 Bits, Bit 7-4
#define     LOG_fTy3MonthMask 0xF0
#define     LOG_fTy3MonthShift 4
#define LOG_fTy4Weekday1                        34      // 1 Bit, Bit 7
#define     LOG_fTy4Weekday1Mask 0x80
#define     LOG_fTy4Weekday1Shift 7
#define LOG_fTy4Weekday2                        34      // 1 Bit, Bit 6
#define     LOG_fTy4Weekday2Mask 0x40
#define     LOG_fTy4Weekday2Shift 6
#define LOG_fTy4Weekday3                        34      // 1 Bit, Bit 5
#define     LOG_fTy4Weekday3Mask 0x20
#define     LOG_fTy4Weekday3Shift 5
#define LOG_fTy4Weekday4                        34      // 1 Bit, Bit 4
#define     LOG_fTy4Weekday4Mask 0x10
#define     LOG_fTy4Weekday4Shift 4
#define LOG_fTy4Weekday5                        34      // 1 Bit, Bit 3
#define     LOG_fTy4Weekday5Mask 0x08
#define     LOG_fTy4Weekday5Shift 3
#define LOG_fTy4Weekday6                        34      // 1 Bit, Bit 2
#define     LOG_fTy4Weekday6Mask 0x04
#define     LOG_fTy4Weekday6Shift 2
#define LOG_fTy4Weekday7                        34      // 1 Bit, Bit 1
#define     LOG_fTy4Weekday7Mask 0x02
#define     LOG_fTy4Weekday7Shift 1
#define LOG_fTy4Day                             34      // 7 Bits, Bit 7-1
#define     LOG_fTy4DayMask 0xFE
#define     LOG_fTy4DayShift 1
#define LOG_fTy4IsWeekday                       34      // 1 Bit, Bit 0
#define     LOG_fTy4IsWeekdayMask 0x01
#define     LOG_fTy4IsWeekdayShift 0
#define LOG_fTy4Month                           35      // 4 Bits, Bit 7-4
#define     LOG_fTy4MonthMask 0xF0
#define     LOG_fTy4MonthShift 4
#define LOG_fI1                                 36      // 2 Bits, Bit 7-6
#define     LOG_fI1Mask 0xC0
#define     LOG_fI1Shift 6
#define LOG_fI2                                 36      // 2 Bits, Bit 5-4
#define     LOG_fI2Mask 0x30
#define     LOG_fI2Shift 4
#define LOG_fI1Kind                             36      // 2 Bits, Bit 3-2
#define     LOG_fI1KindMask 0x0C
#define     LOG_fI1KindShift 2
#define LOG_fI2Kind                             36      // 2 Bits, Bit 1-0
#define     LOG_fI2KindMask 0x03
#define     LOG_fI2KindShift 0
#define LOG_fI1Function                         37      // uint8_t
#define LOG_fI2Function                         38      // uint8_t
#define LOG_fI1FunctionRel                      37      // int8_t
#define LOG_fI2FunctionRel                      38      // int8_t
#define LOG_fI1AsTrigger                        39      // 1 Bit, Bit 7
#define     LOG_fI1AsTriggerMask 0x80
#define     LOG_fI1AsTriggerShift 7
#define LOG_fI2AsTrigger                        39      // 1 Bit, Bit 6
#define     LOG_fI2AsTriggerMask 0x40
#define     LOG_fI2AsTriggerShift 6
#define LOG_fOStairtimeBase                     40      // 2 Bits, Bit 7-6
#define     LOG_fOStairtimeBaseMask 0xC0
#define     LOG_fOStairtimeBaseShift 6
#define LOG_fOStairtimeTime                     40      // 14 Bits, Bit 13-0
#define     LOG_fOStairtimeTimeMask 0x3FFF
#define     LOG_fOStairtimeTimeShift 0
#define LOG_fOBlinkBase                         42      // 2 Bits, Bit 7-6
#define     LOG_fOBlinkBaseMask 0xC0
#define     LOG_fOBlinkBaseShift 6
#define LOG_fOBlinkTime                         42      // 14 Bits, Bit 13-0
#define     LOG_fOBlinkTimeMask 0x3FFF
#define     LOG_fOBlinkTimeShift 0
#define LOG_fODelayOnBase                       44      // 2 Bits, Bit 7-6
#define     LOG_fODelayOnBaseMask 0xC0
#define     LOG_fODelayOnBaseShift 6
#define LOG_fODelayOnTime                       44      // 14 Bits, Bit 13-0
#define     LOG_fODelayOnTimeMask 0x3FFF
#define     LOG_fODelayOnTimeShift 0
#define LOG_fODelayOffBase                      46      // 2 Bits, Bit 7-6
#define     LOG_fODelayOffBaseMask 0xC0
#define     LOG_fODelayOffBaseShift 6
#define LOG_fODelayOffTime                      46      // 14 Bits, Bit 13-0
#define     LOG_fODelayOffTimeMask 0x3FFF
#define     LOG_fODelayOffTimeShift 0
#define LOG_fORepeatOnBase                      48      // 2 Bits, Bit 7-6
#define     LOG_fORepeatOnBaseMask 0xC0
#define     LOG_fORepeatOnBaseShift 6
#define LOG_fORepeatOnTime                      48      // 14 Bits, Bit 13-0
#define     LOG_fORepeatOnTimeMask 0x3FFF
#define     LOG_fORepeatOnTimeShift 0
#define LOG_fORepeatOffBase                     50      // 2 Bits, Bit 7-6
#define     LOG_fORepeatOffBaseMask 0xC0
#define     LOG_fORepeatOffBaseShift 6
#define LOG_fORepeatOffTime                     50      // 14 Bits, Bit 13-0
#define     LOG_fORepeatOffTimeMask 0x3FFF
#define     LOG_fORepeatOffTimeShift 0
#define LOG_fODelay                             52      // 1 Bit, Bit 7
#define     LOG_fODelayMask 0x80
#define     LOG_fODelayShift 7
#define LOG_fODelayOnRepeat                     52      // 2 Bits, Bit 6-5
#define     LOG_fODelayOnRepeatMask 0x60
#define     LOG_fODelayOnRepeatShift 5
#define LOG_fODelayOnReset                      52      // 1 Bit, Bit 4
#define     LOG_fODelayOnResetMask 0x10
#define     LOG_fODelayOnResetShift 4
#define LOG_fODelayOffRepeat                    52      // 2 Bits, Bit 3-2
#define     LOG_fODelayOffRepeatMask 0x0C
#define     LOG_fODelayOffRepeatShift 2
#define LOG_fODelayOffReset                     52      // 1 Bit, Bit 1
#define     LOG_fODelayOffResetMask 0x02
#define     LOG_fODelayOffResetShift 1
#define LOG_fOStair                             52      // 1 Bit, Bit 0
#define     LOG_fOStairMask 0x01
#define     LOG_fOStairShift 0
#define LOG_fORetrigger                         53      // 1 Bit, Bit 7
#define     LOG_fORetriggerMask 0x80
#define     LOG_fORetriggerShift 7
#define LOG_fOStairOff                          53      // 1 Bit, Bit 6
#define     LOG_fOStairOffMask 0x40
#define     LOG_fOStairOffShift 6
#define LOG_fORepeat                            53      // 1 Bit, Bit 5
#define     LOG_fORepeatMask 0x20
#define     LOG_fORepeatShift 5
#define LOG_fOOutputFilter                      53      // 2 Bits, Bit 4-3
#define     LOG_fOOutputFilterMask 0x18
#define     LOG_fOOutputFilterShift 3
#define LOG_fOSendOnChange                      53      // 1 Bit, Bit 2
#define     LOG_fOSendOnChangeMask 0x04
#define     LOG_fOSendOnChangeShift 2
#define LOG_fODpt                               54      // 8 Bits, Bit 7-0
#define LOG_fOOn                                55      // 8 Bits, Bit 7-0
#define LOG_fOOnBuzzer                          55      // 8 Bits, Bit 7-0
#define LOG_fOOnLed                             55      // 8 Bits, Bit 7-0
#define LOG_fOOnAll                             55      // 8 Bits, Bit 7-0
#define LOG_fOOnTone                            56      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt1                            56      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt2                            56      // 8 Bits, Bit 7-0
#define LOG_fOOnDpt5                            56      // uint8_t
#define LOG_fOOnDpt5001                         56      // uint8_t
#define LOG_fOOnDpt6                            56      // int8_t
#define LOG_fOOnDpt7                            56      // uint16_t
#define LOG_fOOnDpt8                            56      // int16_t
#define LOG_fOOnDpt9                            56      // float
#define LOG_fOOnDpt12                           56      // uint32_t
#define LOG_fOOnDpt13                           56      // int32_t
#define LOG_fOOnDpt14                           56      // float
#define LOG_fOOnDpt16                           56      // char*, 14 Byte
#define LOG_fOOnDpt17                           56      // 8 Bits, Bit 7-0
#define LOG_fOOnRGB                             56      // 24 Bits, Bit 31-8
#define     LOG_fOOnRGBMask 0xFFFFFF00
#define     LOG_fOOnRGBShift 8
#define LOG_fOOnPAArea                          56      // 4 Bits, Bit 7-4
#define     LOG_fOOnPAAreaMask 0xF0
#define     LOG_fOOnPAAreaShift 4
#define LOG_fOOnPALine                          56      // 4 Bits, Bit 3-0
#define     LOG_fOOnPALineMask 0x0F
#define     LOG_fOOnPALineShift 0
#define LOG_fOOnPADevice                        57      // uint8_t
#define LOG_fOOnFunction                        56      // 8 Bits, Bit 7-0
#define LOG_fOOnKOKind                          61      // 2 Bits, Bit 7-6
#define     LOG_fOOnKOKindMask 0xC0
#define     LOG_fOOnKOKindShift 6
#define LOG_fOOnKONumber                        56      // uint16_t
#define LOG_fOOnKONumberRel                     56      // int16_t
#define LOG_fOOnKODpt                           58      // 8 Bits, Bit 7-0
#define LOG_fOOnKOSend                          61      // 2 Bits, Bit 5-4
#define     LOG_fOOnKOSendMask 0x30
#define     LOG_fOOnKOSendShift 4
#define LOG_fOOnKOSendNumber                    62      // uint16_t
#define LOG_fOOnKOSendNumberRel                 62      // int16_t
#define LOG_fOOff                               70      // 8 Bits, Bit 7-0
#define LOG_fOOffBuzzer                         70      // 8 Bits, Bit 7-0
#define LOG_fOOffLed                            70      // 8 Bits, Bit 7-0
#define LOG_fOOffAll                            70      // 8 Bits, Bit 7-0
#define LOG_fOOffTone                           71      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt1                           71      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt2                           71      // 8 Bits, Bit 7-0
#define LOG_fOOffDpt5                           71      // uint8_t
#define LOG_fOOffDpt5001                        71      // uint8_t
#define LOG_fOOffDpt6                           71      // int8_t
#define LOG_fOOffDpt7                           71      // uint16_t
#define LOG_fOOffDpt8                           71      // int16_t
#define LOG_fOOffDpt9                           71      // float
#define LOG_fOOffDpt12                          71      // uint32_t
#define LOG_fOOffDpt13                          71      // int32_t
#define LOG_fOOffDpt14                          71      // float
#define LOG_fOOffDpt16                          71      // char*, 14 Byte
#define LOG_fOOffDpt17                          71      // 8 Bits, Bit 7-0
#define LOG_fOOffRGB                            71      // 24 Bits, Bit 31-8
#define     LOG_fOOffRGBMask 0xFFFFFF00
#define     LOG_fOOffRGBShift 8
#define LOG_fOOffPAArea                         71      // 4 Bits, Bit 7-4
#define     LOG_fOOffPAAreaMask 0xF0
#define     LOG_fOOffPAAreaShift 4
#define LOG_fOOffPALine                         71      // 4 Bits, Bit 3-0
#define     LOG_fOOffPALineMask 0x0F
#define     LOG_fOOffPALineShift 0
#define LOG_fOOffPADevice                       72      // uint8_t
#define LOG_fOOffFunction                       71      // 8 Bits, Bit 7-0
#define LOG_fOOffKOKind                         76      // 2 Bits, Bit 7-6
#define     LOG_fOOffKOKindMask 0xC0
#define     LOG_fOOffKOKindShift 6
#define LOG_fOOffKONumber                       71      // uint16_t
#define LOG_fOOffKONumberRel                    71      // int16_t
#define LOG_fOOffKODpt                          73      // 8 Bits, Bit 7-0
#define LOG_fOOffKOSend                         76      // 2 Bits, Bit 5-4
#define     LOG_fOOffKOSendMask 0x30
#define     LOG_fOOffKOSendShift 4
#define LOG_fOOffKOSendNumber                   77      // uint16_t
#define LOG_fOOffKOSendNumberRel                77      // int16_t

// Zeit bis der Kanal nach einem Neustart aktiv wird
#define ParamLOG_fChannelDelayBase                   ((knx.paramByte(LOG_ParamCalcIndex(LOG_fChannelDelayBase)) & LOG_fChannelDelayBaseMask) >> LOG_fChannelDelayBaseShift)
// Zeit bis der Kanal nach einem Neustart aktiv wird
#define ParamLOG_fChannelDelayTime                   (knx.paramWord(LOG_ParamCalcIndex(LOG_fChannelDelayTime)) & LOG_fChannelDelayTimeMask)
// Zeit bis der Kanal nach einem Neustart aktiv wird (in Millisekunden)
#define ParamLOG_fChannelDelayTimeMS                 (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fChannelDelayTime))))
// Logik-Operation
#define ParamLOG_fLogic                              (knx.paramByte(LOG_ParamCalcIndex(LOG_fLogic)))
// Logik auswerten
#define ParamLOG_fCalculate                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fCalculate)) & LOG_fCalculateMask)
// Kanal deaktivieren (zu Testzwecken)
#define ParamLOG_fDisable                            ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fDisable)) & LOG_fDisableMask))
// Alarmausgabe (Buzzer oder LED trotz Sperre schalten)?
#define ParamLOG_fAlarm                              ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fAlarm)) & LOG_fAlarmMask))
// Tor geht sofort wieder zu
#define ParamLOG_fTGate                              ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTGate)) & LOG_fTGateMask))
// Wert EIN intern weiterleiten
#define ParamLOG_fOInternalOn                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fOInternalOn)) & LOG_fOInternalOnMask))
// Wert AUS intern weiterleiten
#define ParamLOG_fOInternalOff                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fOInternalOff)) & LOG_fOInternalOffMask))
// Logik sendet ihren Wert weiter
#define ParamLOG_fTrigger                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fTrigger)))
//           Eingang 1
#define ParamLOG_fTriggerE1                          ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerE1)) & LOG_fTriggerE1Mask))
//           Eingang 2
#define ParamLOG_fTriggerE2                          ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerE2)) & LOG_fTriggerE2Mask))
//           Interner Eingang 3
#define ParamLOG_fTriggerI1                          ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerI1)) & LOG_fTriggerI1Mask))
//           Interner Eingang 4
#define ParamLOG_fTriggerI2                          ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerI2)) & LOG_fTriggerI2Mask))
// Logik sendet ihren Wert weiter
#define ParamLOG_fTriggerTime                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerTime)))
// Beim schließen vom Tor wird
#define ParamLOG_fTriggerGateClose                   ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerGateClose)) & LOG_fTriggerGateCloseMask) >> LOG_fTriggerGateCloseShift)
// Beim öffnen vom Tor wird
#define ParamLOG_fTriggerGateOpen                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTriggerGateOpen)) & LOG_fTriggerGateOpenMask) >> LOG_fTriggerGateOpenShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE1ConvertInt                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1ConvertInt)) & LOG_fE1ConvertIntMask) >> LOG_fE1ConvertIntShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE1Convert                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Convert)) & LOG_fE1ConvertMask) >> LOG_fE1ConvertShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE1ConvertFloat                     ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1ConvertFloat)) & LOG_fE1ConvertFloatMask) >> LOG_fE1ConvertFloatShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE1ConvertSpecial                   ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1ConvertSpecial)) & LOG_fE1ConvertSpecialMask) >> LOG_fE1ConvertSpecialShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE1ConvertBool                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1ConvertBool)) & LOG_fE1ConvertBoolMask) >> LOG_fE1ConvertBoolShift)
// Eingang 1
#define ParamLOG_fE1                                 (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1)) & LOG_fE1Mask)
// DPT für Eingang
#define ParamLOG_fE1Dpt                              (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Dpt)))
// Eingang wird gelesen alle
#define ParamLOG_fE1RepeatBase                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1RepeatBase)) & LOG_fE1RepeatBaseMask) >> LOG_fE1RepeatBaseShift)
// Eingang wird gelesen alle
#define ParamLOG_fE1RepeatTime                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1RepeatTime)) & LOG_fE1RepeatTimeMask)
// Eingang wird gelesen alle (in Millisekunden)
#define ParamLOG_fE1RepeatTimeMS                     (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fE1RepeatTime))))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fE1OtherKO                          (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1OtherKO)))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fE1OtherKORel                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1OtherKORel)))
// Falls Vorbelegung aus dem Speicher nicht möglich oder nicht gewünscht, dann vorbelegen mit
#define ParamLOG_fE1Default                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Default)) & LOG_fE1DefaultMask)
// Eingang vorbelegen mit
#define ParamLOG_fE1DefaultExt                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1DefaultExt)) & LOG_fE1DefaultExtMask)
// Eingangswert speichern und beim nächsten Neustart als Vorbelegung nutzen?
#define ParamLOG_fE1DefaultEEPROM                    ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1DefaultEEPROM)) & LOG_fE1DefaultEEPROMMask))
// Nur so lange zyklisch lesen, bis erstes Telegramm eingeht
#define ParamLOG_fE1DefaultRepeat                    ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1DefaultRepeat)) & LOG_fE1DefaultRepeatMask))
// Kommunikationsobjekt für Eingang
#define ParamLOG_fE1UseOtherKO                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE1UseOtherKO)) & LOG_fE1UseOtherKOMask) >> LOG_fE1UseOtherKOShift)
// Von-Wert
#define ParamLOG_fE1LowDelta                         ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDelta)))
// Bis-Wert
#define ParamLOG_fE1HighDelta                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1HighDelta)))
// Von-Wert
#define ParamLOG_fE1LowDeltaFloat                    (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDeltaFloat), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE1HighDeltaFloat                   (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1HighDeltaFloat), Float_Enc_IEEE754Single))
// Von-Wert
#define ParamLOG_fE1LowDeltaDouble                   (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDeltaDouble), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE1HighDeltaDouble                  (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1HighDeltaDouble), Float_Enc_IEEE754Single))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low0Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Valid)) & LOG_fE1Low0ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low1Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Valid)) & LOG_fE1Low1ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low2Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Valid)) & LOG_fE1Low2ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low3Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Valid)) & LOG_fE1Low3ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low4Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low4Valid)) & LOG_fE1Low4ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low5Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low5Valid)) & LOG_fE1Low5ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE1Low6Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low6Valid)) & LOG_fE1Low6ValidMask))
// Eingang ist EIN, wenn Wert gleich
#define ParamLOG_fE1Low0Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE1Low1Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE1Low2Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE1Low3Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt2)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt2Fix                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt2Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt5                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt5)))
// Bis-Wert
#define ParamLOG_fE1HighDpt5                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1HighDpt5)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE1Low0Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low1Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low2Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low3Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low4Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low4Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low5Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low5Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE1Low6Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low6Dpt5In)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt5Fix                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt5Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt5001                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt5001)))
// Bis-Wert
#define ParamLOG_fE1HighDpt5001                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1HighDpt5001)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE1Low0Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low1Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low2Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low3Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low4Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low4Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low5Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low5Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE1Low6Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low6Dpt5xIn)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt5xFix                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt5xFix)))
// Von-Wert
#define ParamLOG_fE1LowDpt6                          ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt6)))
// Bis-Wert
#define ParamLOG_fE1HighDpt6                         ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1HighDpt6)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE1Low0Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low1Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low2Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low3Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low4Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low4Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low5Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low5Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE1Low6Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low6Dpt6In)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt6Fix                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt6Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt7                          (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1LowDpt7)))
// Bis-Wert
#define ParamLOG_fE1HighDpt7                         (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1HighDpt7)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE1Low0Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low0Dpt7In)))
// ... oder bei Wert
#define ParamLOG_fE1Low1Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low1Dpt7In)))
// ... oder bei Wert
#define ParamLOG_fE1Low2Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low2Dpt7In)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt7Fix                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE1LowDpt7Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt8                          ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1LowDpt8)))
// Bis-Wert
#define ParamLOG_fE1HighDpt8                         ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1HighDpt8)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE1Low0Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low0Dpt8In)))
// ... oder bei Wert
#define ParamLOG_fE1Low1Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low1Dpt8In)))
// ... oder bei Wert
#define ParamLOG_fE1Low2Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1Low2Dpt8In)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt8Fix                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE1LowDpt8Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt9                          (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDpt9), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE1HighDpt9                         (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1HighDpt9), Float_Enc_IEEE754Single))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt9Fix                       (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDpt9Fix), Float_Enc_IEEE754Single))
// Von-Wert
#define ParamLOG_fE1LowDpt12                         (knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDpt12)))
// Bis-Wert
#define ParamLOG_fE1HighDpt12                        (knx.paramInt(LOG_ParamCalcIndex(LOG_fE1HighDpt12)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt12Fix                      (knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDpt12Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt13                         ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDpt13)))
// Bis-Wert
#define ParamLOG_fE1HighDpt13                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1HighDpt13)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt13Fix                      ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDpt13Fix)))
// Von-Wert
#define ParamLOG_fE1LowDpt14                         (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDpt14), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE1HighDpt14                        (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1HighDpt14), Float_Enc_IEEE754Single))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt14Fix                      (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE1LowDpt14Fix), Float_Enc_IEEE754Single))
// Eingang ist EIN bei Szene
#define ParamLOG_fE1Low0Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low0Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low1Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low1Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low2Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low2Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low3Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low3Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low4Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low4Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low5Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low5Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low6Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low6Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE1Low7Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1Low7Dpt17)))
// Eingang ist konstant
#define ParamLOG_fE1LowDpt17Fix                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE1LowDpt17Fix)))
// Von-Wert
#define ParamLOG_fE1LowDptRGB                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDptRGB)))
// Bis-Wert
#define ParamLOG_fE1HighDptRGB                       ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1HighDptRGB)))
// Eingang ist konstant
#define ParamLOG_fE1LowDptRGBFix                     ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE1LowDptRGBFix)))
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE2ConvertInt                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2ConvertInt)) & LOG_fE2ConvertIntMask) >> LOG_fE2ConvertIntShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE2Convert                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Convert)) & LOG_fE2ConvertMask) >> LOG_fE2ConvertShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE2ConvertFloat                     ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2ConvertFloat)) & LOG_fE2ConvertFloatMask) >> LOG_fE2ConvertFloatShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE2ConvertSpecial                   ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2ConvertSpecial)) & LOG_fE2ConvertSpecialMask) >> LOG_fE2ConvertSpecialShift)
// Wert für Eingang wird ermittelt durch
#define ParamLOG_fE2ConvertBool                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2ConvertBool)) & LOG_fE2ConvertBoolMask) >> LOG_fE2ConvertBoolShift)
// Eingang 2
#define ParamLOG_fE2                                 (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2)) & LOG_fE2Mask)
// DPT für Eingang
#define ParamLOG_fE2Dpt                              (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Dpt)))
// Eingang wird gelesen alle
#define ParamLOG_fE2RepeatBase                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2RepeatBase)) & LOG_fE2RepeatBaseMask) >> LOG_fE2RepeatBaseShift)
// Eingang wird gelesen alle
#define ParamLOG_fE2RepeatTime                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2RepeatTime)) & LOG_fE2RepeatTimeMask)
// Eingang wird gelesen alle (in Millisekunden)
#define ParamLOG_fE2RepeatTimeMS                     (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fE2RepeatTime))))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fE2OtherKO                          (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2OtherKO)))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fE2OtherKORel                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2OtherKORel)))
// Falls Vorbelegung aus dem Speicher nicht möglich oder nicht gewünscht, dann vorbelegen mit
#define ParamLOG_fE2Default                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Default)) & LOG_fE2DefaultMask)
// Eingang vorbelegen mit
#define ParamLOG_fE2DefaultExt                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2DefaultExt)) & LOG_fE2DefaultExtMask)
// Eingangswert speichern und beim nächsten Neustart als Vorbelegung nutzen?
#define ParamLOG_fE2DefaultEEPROM                    ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2DefaultEEPROM)) & LOG_fE2DefaultEEPROMMask))
// Nur so lange zyklisch lesen, bis erstes Telegramm eingeht
#define ParamLOG_fE2DefaultRepeat                    ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2DefaultRepeat)) & LOG_fE2DefaultRepeatMask))
// Kommunikationsobjekt für Eingang
#define ParamLOG_fE2UseOtherKO                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fE2UseOtherKO)) & LOG_fE2UseOtherKOMask) >> LOG_fE2UseOtherKOShift)
// Von-Wert
#define ParamLOG_fE2LowDelta                         ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDelta)))
// Bis-Wert
#define ParamLOG_fE2HighDelta                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2HighDelta)))
// Von-Wert
#define ParamLOG_fE2LowDeltaFloat                    (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDeltaFloat), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE2HighDeltaFloat                   (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2HighDeltaFloat), Float_Enc_IEEE754Single))
// Von-Wert
#define ParamLOG_fE2LowDeltaDouble                   (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDeltaDouble), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE2HighDeltaDouble                  (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2HighDeltaDouble), Float_Enc_IEEE754Single))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low0Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Valid)) & LOG_fE2Low0ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low1Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Valid)) & LOG_fE2Low1ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low2Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Valid)) & LOG_fE2Low2ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low3Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Valid)) & LOG_fE2Low3ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low4Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low4Valid)) & LOG_fE2Low4ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low5Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low5Valid)) & LOG_fE2Low5ValidMask))
// Nächste Zeile auswerten?
#define ParamLOG_fE2Low6Valid                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low6Valid)) & LOG_fE2Low6ValidMask))
// Eingang ist EIN, wenn Wert gleich
#define ParamLOG_fE2Low0Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE2Low1Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE2Low2Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt2)))
// ... oder wenn Wert gleich 
#define ParamLOG_fE2Low3Dpt2                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt2)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt2Fix                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt2Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt5                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt5)))
// Bis-Wert
#define ParamLOG_fE2HighDpt5                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2HighDpt5)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE2Low0Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low1Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low2Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low3Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low4Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low4Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low5Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low5Dpt5In)))
// ... oder bei Wert
#define ParamLOG_fE2Low6Dpt5In                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low6Dpt5In)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt5Fix                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt5Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt5001                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt5001)))
// Bis-Wert
#define ParamLOG_fE2HighDpt5001                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2HighDpt5001)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE2Low0Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low1Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low2Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low3Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low4Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low4Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low5Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low5Dpt5xIn)))
// ... oder bei Wert
#define ParamLOG_fE2Low6Dpt5xIn                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low6Dpt5xIn)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt5xFix                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt5xFix)))
// Von-Wert
#define ParamLOG_fE2LowDpt6                          ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt6)))
// Bis-Wert
#define ParamLOG_fE2HighDpt6                         ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2HighDpt6)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE2Low0Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low1Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low2Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low3Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low4Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low4Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low5Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low5Dpt6In)))
// ... oder bei Wert
#define ParamLOG_fE2Low6Dpt6In                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low6Dpt6In)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt6Fix                       ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt6Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt7                          (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2LowDpt7)))
// Bis-Wert
#define ParamLOG_fE2HighDpt7                         (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2HighDpt7)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE2Low0Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low0Dpt7In)))
// ... oder bei Wert
#define ParamLOG_fE2Low1Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low1Dpt7In)))
// ... oder bei Wert
#define ParamLOG_fE2Low2Dpt7In                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low2Dpt7In)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt7Fix                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fE2LowDpt7Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt8                          ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2LowDpt8)))
// Bis-Wert
#define ParamLOG_fE2HighDpt8                         ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2HighDpt8)))
// Eingang ist EIN bei Wert
#define ParamLOG_fE2Low0Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low0Dpt8In)))
// ... oder bei Wert
#define ParamLOG_fE2Low1Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low1Dpt8In)))
// ... oder bei Wert
#define ParamLOG_fE2Low2Dpt8In                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2Low2Dpt8In)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt8Fix                       ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fE2LowDpt8Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt9                          (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDpt9), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE2HighDpt9                         (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2HighDpt9), Float_Enc_IEEE754Single))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt9Fix                       (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDpt9Fix), Float_Enc_IEEE754Single))
// Von-Wert
#define ParamLOG_fE2LowDpt12                         (knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDpt12)))
// Bis-Wert
#define ParamLOG_fE2HighDpt12                        (knx.paramInt(LOG_ParamCalcIndex(LOG_fE2HighDpt12)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt12Fix                      (knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDpt12Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt13                         ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDpt13)))
// Bis-Wert
#define ParamLOG_fE2HighDpt13                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2HighDpt13)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt13Fix                      ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDpt13Fix)))
// Von-Wert
#define ParamLOG_fE2LowDpt14                         (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDpt14), Float_Enc_IEEE754Single))
// Bis-Wert
#define ParamLOG_fE2HighDpt14                        (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2HighDpt14), Float_Enc_IEEE754Single))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt14Fix                      (knx.paramFloat(LOG_ParamCalcIndex(LOG_fE2LowDpt14Fix), Float_Enc_IEEE754Single))
// Eingang ist EIN bei Szene
#define ParamLOG_fE2Low0Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low0Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low1Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low1Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low2Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low2Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low3Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low3Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low4Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low4Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low5Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low5Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low6Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low6Dpt17)))
// ... oder bei Szene
#define ParamLOG_fE2Low7Dpt17                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2Low7Dpt17)))
// Eingang ist konstant
#define ParamLOG_fE2LowDpt17Fix                      (knx.paramByte(LOG_ParamCalcIndex(LOG_fE2LowDpt17Fix)))
// Von-Wert
#define ParamLOG_fE2LowDptRGB                        ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDptRGB)))
// Bis-Wert
#define ParamLOG_fE2HighDptRGB                       ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2HighDptRGB)))
// Eingang ist konstant
#define ParamLOG_fE2LowDptRGBFix                     ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fE2LowDptRGBFix)))
// Zeitbezug
#define ParamLOG_fTd1DuskDawn                        ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1DuskDawn)) & LOG_fTd1DuskDawnMask) >> LOG_fTd1DuskDawnShift)
// Zeitbezug
#define ParamLOG_fTd2DuskDawn                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2DuskDawn)) & LOG_fTd2DuskDawnMask)
// Zeitbezug
#define ParamLOG_fTd3DuskDawn                        ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3DuskDawn)) & LOG_fTd3DuskDawnMask) >> LOG_fTd3DuskDawnShift)
// Zeitbezug
#define ParamLOG_fTd4DuskDawn                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4DuskDawn)) & LOG_fTd4DuskDawnMask)
// Zeitbezug
#define ParamLOG_fTd5DuskDawn                        ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5DuskDawn)) & LOG_fTd5DuskDawnMask) >> LOG_fTd5DuskDawnShift)
// Zeitbezug
#define ParamLOG_fTd6DuskDawn                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6DuskDawn)) & LOG_fTd6DuskDawnMask)
// Zeitbezug
#define ParamLOG_fTd7DuskDawn                        ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7DuskDawn)) & LOG_fTd7DuskDawnMask) >> LOG_fTd7DuskDawnShift)
// Zeitbezug
#define ParamLOG_fTd8DuskDawn                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8DuskDawn)) & LOG_fTd8DuskDawnMask)
// Typ der Zeitschaltuhr
#define ParamLOG_fTYearDay                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTYearDay)) & LOG_fTYearDayMask) >> LOG_fTYearDayShift)
// Feiertagsbehandlung
#define ParamLOG_fTHoliday                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTHoliday)) & LOG_fTHolidayMask) >> LOG_fTHolidayShift)
// Bei Neustart letzte Schaltzeit nachholen
#define ParamLOG_fTRestoreState                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTRestoreState)) & LOG_fTRestoreStateMask) >> LOG_fTRestoreStateShift)
// Urlaubsbehandlung
#define ParamLOG_fTVacation                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fTVacation)) & LOG_fTVacationMask)
// Zahlenwert
#define ParamLOG_fTd1ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1ValueNum)))
// Zahlenwert
#define ParamLOG_fTd2ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2ValueNum)))
// Zahlenwert
#define ParamLOG_fTd3ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3ValueNum)))
// Zahlenwert
#define ParamLOG_fTd4ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4ValueNum)))
// Zahlenwert
#define ParamLOG_fTd5ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5ValueNum)))
// Zahlenwert
#define ParamLOG_fTd6ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6ValueNum)))
// Zahlenwert
#define ParamLOG_fTd7ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7ValueNum)))
// Zahlenwert
#define ParamLOG_fTd8ValueNum                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8ValueNum)))
// Schaltwert
#define ParamLOG_fTd1Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1Value)) & LOG_fTd1ValueMask))
// Grad
#define ParamLOG_fTd1Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1Degree)) & LOG_fTd1DegreeMask) >> LOG_fTd1DegreeShift)
// Stunde
#define ParamLOG_fTd1HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1HourAbs)) & LOG_fTd1HourAbsMask) >> LOG_fTd1HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd1HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1HourRel)) & LOG_fTd1HourRelMask) >> LOG_fTd1HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd1HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1HourRelShort)) & LOG_fTd1HourRelShortMask) >> LOG_fTd1HourRelShortShift)
// Minute
#define ParamLOG_fTd1MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1MinuteAbs)))
// Minute
#define ParamLOG_fTd1MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1MinuteRel)))
// Wochentag
#define ParamLOG_fTd1Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd1Weekday)) & LOG_fTd1WeekdayMask)
// Schaltwert
#define ParamLOG_fTd2Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2Value)) & LOG_fTd2ValueMask))
// Grad
#define ParamLOG_fTd2Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2Degree)) & LOG_fTd2DegreeMask) >> LOG_fTd2DegreeShift)
// Stunde
#define ParamLOG_fTd2HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2HourAbs)) & LOG_fTd2HourAbsMask) >> LOG_fTd2HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd2HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2HourRel)) & LOG_fTd2HourRelMask) >> LOG_fTd2HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd2HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2HourRelShort)) & LOG_fTd2HourRelShortMask) >> LOG_fTd2HourRelShortShift)
// Minute
#define ParamLOG_fTd2MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2MinuteAbs)))
// Minute
#define ParamLOG_fTd2MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2MinuteRel)))
// Wochentag
#define ParamLOG_fTd2Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd2Weekday)) & LOG_fTd2WeekdayMask)
// Schaltwert
#define ParamLOG_fTd3Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3Value)) & LOG_fTd3ValueMask))
// Grad
#define ParamLOG_fTd3Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3Degree)) & LOG_fTd3DegreeMask) >> LOG_fTd3DegreeShift)
// Stunde
#define ParamLOG_fTd3HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3HourAbs)) & LOG_fTd3HourAbsMask) >> LOG_fTd3HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd3HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3HourRel)) & LOG_fTd3HourRelMask) >> LOG_fTd3HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd3HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3HourRelShort)) & LOG_fTd3HourRelShortMask) >> LOG_fTd3HourRelShortShift)
// Minute
#define ParamLOG_fTd3MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3MinuteAbs)))
// Minute
#define ParamLOG_fTd3MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3MinuteRel)))
// Wochentag
#define ParamLOG_fTd3Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd3Weekday)) & LOG_fTd3WeekdayMask)
// Schaltwert
#define ParamLOG_fTd4Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4Value)) & LOG_fTd4ValueMask))
// Grad
#define ParamLOG_fTd4Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4Degree)) & LOG_fTd4DegreeMask) >> LOG_fTd4DegreeShift)
// Stunde
#define ParamLOG_fTd4HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4HourAbs)) & LOG_fTd4HourAbsMask) >> LOG_fTd4HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd4HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4HourRel)) & LOG_fTd4HourRelMask) >> LOG_fTd4HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd4HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4HourRelShort)) & LOG_fTd4HourRelShortMask) >> LOG_fTd4HourRelShortShift)
// Minute
#define ParamLOG_fTd4MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4MinuteAbs)))
// Minute
#define ParamLOG_fTd4MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4MinuteRel)))
// Wochentag
#define ParamLOG_fTd4Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd4Weekday)) & LOG_fTd4WeekdayMask)
// Schaltwert
#define ParamLOG_fTd5Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5Value)) & LOG_fTd5ValueMask))
// Grad
#define ParamLOG_fTd5Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5Degree)) & LOG_fTd5DegreeMask) >> LOG_fTd5DegreeShift)
// Stunde
#define ParamLOG_fTd5HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5HourAbs)) & LOG_fTd5HourAbsMask) >> LOG_fTd5HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd5HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5HourRel)) & LOG_fTd5HourRelMask) >> LOG_fTd5HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd5HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5HourRelShort)) & LOG_fTd5HourRelShortMask) >> LOG_fTd5HourRelShortShift)
// Minute
#define ParamLOG_fTd5MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5MinuteAbs)))
// Minute
#define ParamLOG_fTd5MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5MinuteRel)))
// Wochentag
#define ParamLOG_fTd5Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd5Weekday)) & LOG_fTd5WeekdayMask)
// Schaltwert
#define ParamLOG_fTd6Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6Value)) & LOG_fTd6ValueMask))
// Grad
#define ParamLOG_fTd6Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6Degree)) & LOG_fTd6DegreeMask) >> LOG_fTd6DegreeShift)
// Stunde
#define ParamLOG_fTd6HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6HourAbs)) & LOG_fTd6HourAbsMask) >> LOG_fTd6HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd6HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6HourRel)) & LOG_fTd6HourRelMask) >> LOG_fTd6HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd6HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6HourRelShort)) & LOG_fTd6HourRelShortMask) >> LOG_fTd6HourRelShortShift)
// Minute
#define ParamLOG_fTd6MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6MinuteAbs)))
// Minute
#define ParamLOG_fTd6MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6MinuteRel)))
// Wochentag
#define ParamLOG_fTd6Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd6Weekday)) & LOG_fTd6WeekdayMask)
// Schaltwert
#define ParamLOG_fTd7Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7Value)) & LOG_fTd7ValueMask))
// Grad
#define ParamLOG_fTd7Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7Degree)) & LOG_fTd7DegreeMask) >> LOG_fTd7DegreeShift)
// Stunde
#define ParamLOG_fTd7HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7HourAbs)) & LOG_fTd7HourAbsMask) >> LOG_fTd7HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd7HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7HourRel)) & LOG_fTd7HourRelMask) >> LOG_fTd7HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd7HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7HourRelShort)) & LOG_fTd7HourRelShortMask) >> LOG_fTd7HourRelShortShift)
// Minute
#define ParamLOG_fTd7MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7MinuteAbs)))
// Minute
#define ParamLOG_fTd7MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7MinuteRel)))
// Wochentag
#define ParamLOG_fTd7Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd7Weekday)) & LOG_fTd7WeekdayMask)
// Schaltwert
#define ParamLOG_fTd8Value                           ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8Value)) & LOG_fTd8ValueMask))
// Grad
#define ParamLOG_fTd8Degree                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8Degree)) & LOG_fTd8DegreeMask) >> LOG_fTd8DegreeShift)
// Stunde
#define ParamLOG_fTd8HourAbs                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8HourAbs)) & LOG_fTd8HourAbsMask) >> LOG_fTd8HourAbsShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd8HourRel                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8HourRel)) & LOG_fTd8HourRelMask) >> LOG_fTd8HourRelShift)
// Sonnen auf-/untergang
#define ParamLOG_fTd8HourRelShort                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8HourRelShort)) & LOG_fTd8HourRelShortMask) >> LOG_fTd8HourRelShortShift)
// Minute
#define ParamLOG_fTd8MinuteAbs                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8MinuteAbs)))
// Minute
#define ParamLOG_fTd8MinuteRel                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8MinuteRel)))
// Wochentag
#define ParamLOG_fTd8Weekday                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fTd8Weekday)) & LOG_fTd8WeekdayMask)
// Mo
#define ParamLOG_fTy1Weekday1                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday1)) & LOG_fTy1Weekday1Mask))
// Di
#define ParamLOG_fTy1Weekday2                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday2)) & LOG_fTy1Weekday2Mask))
// Mi
#define ParamLOG_fTy1Weekday3                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday3)) & LOG_fTy1Weekday3Mask))
// Do
#define ParamLOG_fTy1Weekday4                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday4)) & LOG_fTy1Weekday4Mask))
// Fr
#define ParamLOG_fTy1Weekday5                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday5)) & LOG_fTy1Weekday5Mask))
// Sa
#define ParamLOG_fTy1Weekday6                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday6)) & LOG_fTy1Weekday6Mask))
// So
#define ParamLOG_fTy1Weekday7                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Weekday7)) & LOG_fTy1Weekday7Mask))
// Tag
#define ParamLOG_fTy1Day                             ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Day)) & LOG_fTy1DayMask) >> LOG_fTy1DayShift)
// Wochentag
#define ParamLOG_fTy1IsWeekday                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1IsWeekday)) & LOG_fTy1IsWeekdayMask))
// Monat
#define ParamLOG_fTy1Month                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy1Month)) & LOG_fTy1MonthMask) >> LOG_fTy1MonthShift)
// Mo
#define ParamLOG_fTy2Weekday1                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday1)) & LOG_fTy2Weekday1Mask))
// Di
#define ParamLOG_fTy2Weekday2                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday2)) & LOG_fTy2Weekday2Mask))
// Mi
#define ParamLOG_fTy2Weekday3                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday3)) & LOG_fTy2Weekday3Mask))
// Do
#define ParamLOG_fTy2Weekday4                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday4)) & LOG_fTy2Weekday4Mask))
// Fr
#define ParamLOG_fTy2Weekday5                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday5)) & LOG_fTy2Weekday5Mask))
// Sa
#define ParamLOG_fTy2Weekday6                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday6)) & LOG_fTy2Weekday6Mask))
// So
#define ParamLOG_fTy2Weekday7                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Weekday7)) & LOG_fTy2Weekday7Mask))
// Tag
#define ParamLOG_fTy2Day                             ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Day)) & LOG_fTy2DayMask) >> LOG_fTy2DayShift)
// Wochentag
#define ParamLOG_fTy2IsWeekday                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2IsWeekday)) & LOG_fTy2IsWeekdayMask))
// Monat
#define ParamLOG_fTy2Month                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy2Month)) & LOG_fTy2MonthMask) >> LOG_fTy2MonthShift)
// Mo
#define ParamLOG_fTy3Weekday1                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday1)) & LOG_fTy3Weekday1Mask))
// Di
#define ParamLOG_fTy3Weekday2                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday2)) & LOG_fTy3Weekday2Mask))
// Mi
#define ParamLOG_fTy3Weekday3                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday3)) & LOG_fTy3Weekday3Mask))
// Do
#define ParamLOG_fTy3Weekday4                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday4)) & LOG_fTy3Weekday4Mask))
// Fr
#define ParamLOG_fTy3Weekday5                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday5)) & LOG_fTy3Weekday5Mask))
// Sa
#define ParamLOG_fTy3Weekday6                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday6)) & LOG_fTy3Weekday6Mask))
// So
#define ParamLOG_fTy3Weekday7                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Weekday7)) & LOG_fTy3Weekday7Mask))
// Tag
#define ParamLOG_fTy3Day                             ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Day)) & LOG_fTy3DayMask) >> LOG_fTy3DayShift)
// Wochentag
#define ParamLOG_fTy3IsWeekday                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3IsWeekday)) & LOG_fTy3IsWeekdayMask))
// Monat
#define ParamLOG_fTy3Month                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy3Month)) & LOG_fTy3MonthMask) >> LOG_fTy3MonthShift)
// Mo
#define ParamLOG_fTy4Weekday1                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday1)) & LOG_fTy4Weekday1Mask))
// Di
#define ParamLOG_fTy4Weekday2                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday2)) & LOG_fTy4Weekday2Mask))
// Mi
#define ParamLOG_fTy4Weekday3                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday3)) & LOG_fTy4Weekday3Mask))
// Do
#define ParamLOG_fTy4Weekday4                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday4)) & LOG_fTy4Weekday4Mask))
// Fr
#define ParamLOG_fTy4Weekday5                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday5)) & LOG_fTy4Weekday5Mask))
// Sa
#define ParamLOG_fTy4Weekday6                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday6)) & LOG_fTy4Weekday6Mask))
// So
#define ParamLOG_fTy4Weekday7                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Weekday7)) & LOG_fTy4Weekday7Mask))
// Tag
#define ParamLOG_fTy4Day                             ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Day)) & LOG_fTy4DayMask) >> LOG_fTy4DayShift)
// Wochentag
#define ParamLOG_fTy4IsWeekday                       ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4IsWeekday)) & LOG_fTy4IsWeekdayMask))
// Monat
#define ParamLOG_fTy4Month                           ((knx.paramByte(LOG_ParamCalcIndex(LOG_fTy4Month)) & LOG_fTy4MonthMask) >> LOG_fTy4MonthShift)
// Interner Eingang 3
#define ParamLOG_fI1                                 ((knx.paramByte(LOG_ParamCalcIndex(LOG_fI1)) & LOG_fI1Mask) >> LOG_fI1Shift)
// Interner Eingang 4
#define ParamLOG_fI2                                 ((knx.paramByte(LOG_ParamCalcIndex(LOG_fI2)) & LOG_fI2Mask) >> LOG_fI2Shift)
// Art der Verknüpfung
#define ParamLOG_fI1Kind                             ((knx.paramByte(LOG_ParamCalcIndex(LOG_fI1Kind)) & LOG_fI1KindMask) >> LOG_fI1KindShift)
// Art der Verknüpfung
#define ParamLOG_fI2Kind                             (knx.paramByte(LOG_ParamCalcIndex(LOG_fI2Kind)) & LOG_fI2KindMask)
// Internen Eingang verbinden mit Kanal Nr.
#define ParamLOG_fI1Function                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fI1Function)))
// Internen Eingang verbinden mit Kanal Nr.
#define ParamLOG_fI2Function                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fI2Function)))
// Internen Eingang verbinden mit Kanal Nr.
#define ParamLOG_fI1FunctionRel                      ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fI1FunctionRel)))
// Internen Eingang verbinden mit Kanal Nr.
#define ParamLOG_fI2FunctionRel                      ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fI2FunctionRel)))
// Internen Eingang als Trigger nutzen(ist immer logisch EIN)
#define ParamLOG_fI1AsTrigger                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fI1AsTrigger)) & LOG_fI1AsTriggerMask))
// Internen Eingang als Trigger nutzen(ist immer logisch EIN)
#define ParamLOG_fI2AsTrigger                        ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fI2AsTrigger)) & LOG_fI2AsTriggerMask))
// Zeit für Treppenlicht
#define ParamLOG_fOStairtimeBase                     ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOStairtimeBase)) & LOG_fOStairtimeBaseMask) >> LOG_fOStairtimeBaseShift)
// Zeit für Treppenlicht
#define ParamLOG_fOStairtimeTime                     (knx.paramWord(LOG_ParamCalcIndex(LOG_fOStairtimeTime)) & LOG_fOStairtimeTimeMask)
// Zeit für Treppenlicht (in Millisekunden)
#define ParamLOG_fOStairtimeTimeMS                   (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fOStairtimeTime))))
// Treppenlicht blinkt im Rhythmus
#define ParamLOG_fOBlinkBase                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOBlinkBase)) & LOG_fOBlinkBaseMask) >> LOG_fOBlinkBaseShift)
// Treppenlicht blinkt im Rhythmus
#define ParamLOG_fOBlinkTime                         (knx.paramWord(LOG_ParamCalcIndex(LOG_fOBlinkTime)) & LOG_fOBlinkTimeMask)
// Treppenlicht blinkt im Rhythmus (in Millisekunden)
#define ParamLOG_fOBlinkTimeMS                       (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fOBlinkTime))))
// EINschalten wird verzögert um
#define ParamLOG_fODelayOnBase                       ((knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOnBase)) & LOG_fODelayOnBaseMask) >> LOG_fODelayOnBaseShift)
// EINschalten wird verzögert um
#define ParamLOG_fODelayOnTime                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fODelayOnTime)) & LOG_fODelayOnTimeMask)
// EINschalten wird verzögert um (in Millisekunden)
#define ParamLOG_fODelayOnTimeMS                     (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fODelayOnTime))))
// AUSschalten wird verzögert um
#define ParamLOG_fODelayOffBase                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOffBase)) & LOG_fODelayOffBaseMask) >> LOG_fODelayOffBaseShift)
// AUSschalten wird verzögert um
#define ParamLOG_fODelayOffTime                      (knx.paramWord(LOG_ParamCalcIndex(LOG_fODelayOffTime)) & LOG_fODelayOffTimeMask)
// AUSschalten wird verzögert um (in Millisekunden)
#define ParamLOG_fODelayOffTimeMS                    (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fODelayOffTime))))
// EIN-Telegramm wird wiederholt alle
#define ParamLOG_fORepeatOnBase                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fORepeatOnBase)) & LOG_fORepeatOnBaseMask) >> LOG_fORepeatOnBaseShift)
// EIN-Telegramm wird wiederholt alle
#define ParamLOG_fORepeatOnTime                      (knx.paramWord(LOG_ParamCalcIndex(LOG_fORepeatOnTime)) & LOG_fORepeatOnTimeMask)
// EIN-Telegramm wird wiederholt alle (in Millisekunden)
#define ParamLOG_fORepeatOnTimeMS                    (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fORepeatOnTime))))
// AUS-Telegramm wird wiederholt alle
#define ParamLOG_fORepeatOffBase                     ((knx.paramByte(LOG_ParamCalcIndex(LOG_fORepeatOffBase)) & LOG_fORepeatOffBaseMask) >> LOG_fORepeatOffBaseShift)
// AUS-Telegramm wird wiederholt alle
#define ParamLOG_fORepeatOffTime                     (knx.paramWord(LOG_ParamCalcIndex(LOG_fORepeatOffTime)) & LOG_fORepeatOffTimeMask)
// AUS-Telegramm wird wiederholt alle (in Millisekunden)
#define ParamLOG_fORepeatOffTimeMS                   (paramDelay(knx.paramWord(LOG_ParamCalcIndex(LOG_fORepeatOffTime))))
// Ausgang schaltet zeitverzögert
#define ParamLOG_fODelay                             ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fODelay)) & LOG_fODelayMask))
// Erneutes EIN führt zu
#define ParamLOG_fODelayOnRepeat                     ((knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOnRepeat)) & LOG_fODelayOnRepeatMask) >> LOG_fODelayOnRepeatShift)
// Darauffolgendes AUS führt zu
#define ParamLOG_fODelayOnReset                      ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOnReset)) & LOG_fODelayOnResetMask))
// Erneutes AUS führt zu
#define ParamLOG_fODelayOffRepeat                    ((knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOffRepeat)) & LOG_fODelayOffRepeatMask) >> LOG_fODelayOffRepeatShift)
// Darauffolgendes EIN führt zu
#define ParamLOG_fODelayOffReset                     ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fODelayOffReset)) & LOG_fODelayOffResetMask))
// Ausgang hat eine Treppenlichtfunktion
#define ParamLOG_fOStair                             ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fOStair)) & LOG_fOStairMask))
// Treppenlicht kann verlängert werden
#define ParamLOG_fORetrigger                         ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fORetrigger)) & LOG_fORetriggerMask))
// Treppenlicht kann ausgeschaltet werden
#define ParamLOG_fOStairOff                          ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fOStairOff)) & LOG_fOStairOffMask))
// Ausgang wiederholt zyklisch
#define ParamLOG_fORepeat                            ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fORepeat)) & LOG_fORepeatMask))
// Wiederholungsfilter
#define ParamLOG_fOOutputFilter                      ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOutputFilter)) & LOG_fOOutputFilterMask) >> LOG_fOOutputFilterShift)
// Sendeverhalten für Ausgang
#define ParamLOG_fOSendOnChange                      ((bool)(knx.paramByte(LOG_ParamCalcIndex(LOG_fOSendOnChange)) & LOG_fOSendOnChangeMask))
// DPT für Ausgang
#define ParamLOG_fODpt                               (knx.paramByte(LOG_ParamCalcIndex(LOG_fODpt)))
// Wert für EIN senden?
#define ParamLOG_fOOn                                (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOn)))
// Wert für EIN senden?
#define ParamLOG_fOOnBuzzer                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnBuzzer)))
// Wert für EIN senden?
#define ParamLOG_fOOnLed                             (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnLed)))
// Wert für EIN senden?
#define ParamLOG_fOOnAll                             (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnAll)))
//     Wert für EIN senden als
#define ParamLOG_fOOnTone                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnTone)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt1                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt1)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt2                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt2)))
//     Wert für EIN senden als 
#define ParamLOG_fOOnDpt5                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt5)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt5001                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt5001)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt6                            ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt6)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt7                            (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnDpt7)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt8                            ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnDpt8)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt9                            (knx.paramFloat(LOG_ParamCalcIndex(LOG_fOOnDpt9), Float_Enc_IEEE754Single))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt12                           (knx.paramInt(LOG_ParamCalcIndex(LOG_fOOnDpt12)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt13                           ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fOOnDpt13)))
//     Wert für EIN senden als
#define ParamLOG_fOOnDpt14                           (knx.paramFloat(LOG_ParamCalcIndex(LOG_fOOnDpt14), Float_Enc_IEEE754Single))
//     Wert für EIN senden als 
#define ParamLOG_fOOnDpt16                           (knx.paramData(LOG_ParamCalcIndex(LOG_fOOnDpt16)))
//     Wert für EIN senden als 
#define ParamLOG_fOOnDpt17                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnDpt17)))
//     Wert für EIN senden als (3-Byte-RGB)
#define ParamLOG_fOOnRGB                             ((knx.paramInt(LOG_ParamCalcIndex(LOG_fOOnRGB)) & LOG_fOOnRGBMask) >> LOG_fOOnRGBShift)
// 
#define ParamLOG_fOOnPAArea                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnPAArea)) & LOG_fOOnPAAreaMask) >> LOG_fOOnPAAreaShift)
// 
#define ParamLOG_fOOnPALine                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnPALine)) & LOG_fOOnPALineMask)
// 
#define ParamLOG_fOOnPADevice                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnPADevice)))
//     Wert für EIN ermitteln als
#define ParamLOG_fOOnFunction                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnFunction)))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fOOnKOKind                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnKOKind)) & LOG_fOOnKOKindMask) >> LOG_fOOnKOKindShift)
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fOOnKONumber                        (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnKONumber)))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fOOnKONumberRel                     ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnKONumberRel)))
//     DPT des Kommunikationsobjekts
#define ParamLOG_fOOnKODpt                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnKODpt)))
//     Wert für EIN an ein zusätzliches    KO senden?
#define ParamLOG_fOOnKOSend                          ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOnKOSend)) & LOG_fOOnKOSendMask) >> LOG_fOOnKOSendShift)
//         Nummer des zusätzlichen KO
#define ParamLOG_fOOnKOSendNumber                    (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnKOSendNumber)))
//         Nummer des zusätzlichen KO
#define ParamLOG_fOOnKOSendNumberRel                 ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fOOnKOSendNumberRel)))
// Wert für AUS senden?
#define ParamLOG_fOOff                               (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOff)))
// Wert für AUS senden?
#define ParamLOG_fOOffBuzzer                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffBuzzer)))
// Wert für AUS senden?
#define ParamLOG_fOOffLed                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffLed)))
// Wert für AUS senden?
#define ParamLOG_fOOffAll                            (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffAll)))
//     Wert für AUS senden als
#define ParamLOG_fOOffTone                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffTone)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt1                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt1)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt2                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt2)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt5                           (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt5)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt5001                        (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt5001)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt6                           ((int8_t)knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt6)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt7                           (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffDpt7)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt8                           ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffDpt8)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt9                           (knx.paramFloat(LOG_ParamCalcIndex(LOG_fOOffDpt9), Float_Enc_IEEE754Single))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt12                          (knx.paramInt(LOG_ParamCalcIndex(LOG_fOOffDpt12)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt13                          ((int32_t)knx.paramInt(LOG_ParamCalcIndex(LOG_fOOffDpt13)))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt14                          (knx.paramFloat(LOG_ParamCalcIndex(LOG_fOOffDpt14), Float_Enc_IEEE754Single))
//     Wert für AUS senden als
#define ParamLOG_fOOffDpt16                          (knx.paramData(LOG_ParamCalcIndex(LOG_fOOffDpt16)))
//     Wert für AUS senden als 
#define ParamLOG_fOOffDpt17                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffDpt17)))
//     Wert für AUS senden als (3-Byte-RGB)
#define ParamLOG_fOOffRGB                            ((knx.paramInt(LOG_ParamCalcIndex(LOG_fOOffRGB)) & LOG_fOOffRGBMask) >> LOG_fOOffRGBShift)
// 
#define ParamLOG_fOOffPAArea                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffPAArea)) & LOG_fOOffPAAreaMask) >> LOG_fOOffPAAreaShift)
// 
#define ParamLOG_fOOffPALine                         (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffPALine)) & LOG_fOOffPALineMask)
// 
#define ParamLOG_fOOffPADevice                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffPADevice)))
//     Wert für AUS ermitteln als
#define ParamLOG_fOOffFunction                       (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffFunction)))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fOOffKOKind                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffKOKind)) & LOG_fOOffKOKindMask) >> LOG_fOOffKOKindShift)
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fOOffKONumber                       (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffKONumber)))
//     Nummer des Kommunikationsobjekts
#define ParamLOG_fOOffKONumberRel                    ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffKONumberRel)))
//     DPT des Kommunikationsobjekts
#define ParamLOG_fOOffKODpt                          (knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffKODpt)))
//     Wert für AUS an ein zusätzliches    KO senden?
#define ParamLOG_fOOffKOSend                         ((knx.paramByte(LOG_ParamCalcIndex(LOG_fOOffKOSend)) & LOG_fOOffKOSendMask) >> LOG_fOOffKOSendShift)
//         Nummer des zusätzlichen KO
#define ParamLOG_fOOffKOSendNumber                   (knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffKOSendNumber)))
//         Nummer des zusätzlichen KO
#define ParamLOG_fOOffKOSendNumberRel                ((int16_t)knx.paramWord(LOG_ParamCalcIndex(LOG_fOOffKOSendNumberRel)))

// deprecated
#define LOG_KoOffset 100

// Communication objects per channel (multiple occurrence)
#define LOG_KoBlockOffset 100
#define LOG_KoBlockSize 3

#define LOG_KoCalcNumber(index) (index + LOG_KoBlockOffset + _channelIndex * LOG_KoBlockSize)
#define LOG_KoCalcIndex(number) ((number >= LOG_KoCalcNumber(0) && number < LOG_KoCalcNumber(LOG_KoBlockSize)) ? (number - LOG_KoBlockOffset) % LOG_KoBlockSize : -1)
#define LOG_KoCalcChannel(number) ((number >= LOG_KoBlockOffset && number < LOG_KoBlockOffset + LOG_ChannelCount * LOG_KoBlockSize) ? (number - LOG_KoBlockOffset) / LOG_KoBlockSize : -1)

#define LOG_KoKOfE1 0
#define LOG_KoKOfE2 1
#define LOG_KoKOfO 2

// Eingang 1
#define KoLOG_KOfE1                               (knx.getGroupObject(LOG_KoCalcNumber(LOG_KoKOfE1)))
// Eingang 2
#define KoLOG_KOfE2                               (knx.getGroupObject(LOG_KoCalcNumber(LOG_KoKOfE2)))
// Ausgang
#define KoLOG_KOfO                                (knx.getGroupObject(LOG_KoCalcNumber(LOG_KoKOfO)))

#define FCB_VisibleChannels                     13206      // uint8_t

// Verfügbare Kanäle
#define ParamFCB_VisibleChannels                     (knx.paramByte(FCB_VisibleChannels))

#define FCB_ChannelCount 15

// Parameter per channel
#define FCB_ParamBlockOffset 13207
#define FCB_ParamBlockSize 71
#define FCB_ParamCalcIndex(index) (index + FCB_ParamBlockOffset + _channelIndex * FCB_ParamBlockSize)

#define FCB_CHChannelType                        0      // 8 Bits, Bit 7-0
#define FCB_CHChannelDisabled                    1      // 1 Bit, Bit 7
#define     FCB_CHChannelDisabledMask 0x80
#define     FCB_CHChannelDisabledShift 7
#define FCB_CHLogicKo0D                          2      // 2 Bits, Bit 7-6
#define     FCB_CHLogicKo0DMask 0xC0
#define     FCB_CHLogicKo0DShift 6
#define FCB_CHLogicKo1D                          2      // 2 Bits, Bit 5-4
#define     FCB_CHLogicKo1DMask 0x30
#define     FCB_CHLogicKo1DShift 4
#define FCB_CHLogicKo2D                          2      // 2 Bits, Bit 3-2
#define     FCB_CHLogicKo2DMask 0x0C
#define     FCB_CHLogicKo2DShift 2
#define FCB_CHLogicKo3D                          2      // 2 Bits, Bit 1-0
#define     FCB_CHLogicKo3DMask 0x03
#define     FCB_CHLogicKo3DShift 0
#define FCB_CHLogicKo4D                          3      // 2 Bits, Bit 7-6
#define     FCB_CHLogicKo4DMask 0xC0
#define     FCB_CHLogicKo4DShift 6
#define FCB_CHLogicKo5D                          3      // 2 Bits, Bit 5-4
#define     FCB_CHLogicKo5DMask 0x30
#define     FCB_CHLogicKo5DShift 4
#define FCB_CHLogicKo6D                          3      // 2 Bits, Bit 3-2
#define     FCB_CHLogicKo6DMask 0x0C
#define     FCB_CHLogicKo6DShift 2
#define FCB_CHLogicKo7D                          3      // 2 Bits, Bit 1-0
#define     FCB_CHLogicKo7DMask 0x03
#define     FCB_CHLogicKo7DShift 0
#define FCB_CHLogicKo8D                          4      // 2 Bits, Bit 7-6
#define     FCB_CHLogicKo8DMask 0xC0
#define     FCB_CHLogicKo8DShift 6
#define FCB_CHLogicKo9D                          4      // 2 Bits, Bit 5-4
#define     FCB_CHLogicKo9DMask 0x30
#define     FCB_CHLogicKo9DShift 4
#define FCB_CHLogicOutInv                        4      // 1 Bit, Bit 4
#define     FCB_CHLogicOutInvMask 0x10
#define     FCB_CHLogicOutInvShift 4
#define FCB_CHLogicBehavKo0                      5      // 4 Bits, Bit 7-4
#define     FCB_CHLogicBehavKo0Mask 0xF0
#define     FCB_CHLogicBehavKo0Shift 4
#define FCB_CHLogicBehavKo1                      5      // 4 Bits, Bit 3-0
#define     FCB_CHLogicBehavKo1Mask 0x0F
#define     FCB_CHLogicBehavKo1Shift 0
#define FCB_CHLogicBehavKo2                      6      // 4 Bits, Bit 7-4
#define     FCB_CHLogicBehavKo2Mask 0xF0
#define     FCB_CHLogicBehavKo2Shift 4
#define FCB_CHLogicBehavKo3                      6      // 4 Bits, Bit 3-0
#define     FCB_CHLogicBehavKo3Mask 0x0F
#define     FCB_CHLogicBehavKo3Shift 0
#define FCB_CHLogicBehavKo4                      7      // 4 Bits, Bit 7-4
#define     FCB_CHLogicBehavKo4Mask 0xF0
#define     FCB_CHLogicBehavKo4Shift 4
#define FCB_CHLogicBehavKo5                      7      // 4 Bits, Bit 3-0
#define     FCB_CHLogicBehavKo5Mask 0x0F
#define     FCB_CHLogicBehavKo5Shift 0
#define FCB_CHLogicBehavKo6                      8      // 4 Bits, Bit 7-4
#define     FCB_CHLogicBehavKo6Mask 0xF0
#define     FCB_CHLogicBehavKo6Shift 4
#define FCB_CHLogicBehavKo7                      8      // 4 Bits, Bit 3-0
#define     FCB_CHLogicBehavKo7Mask 0x0F
#define     FCB_CHLogicBehavKo7Shift 0
#define FCB_CHLogicBehavKo8                      9      // 4 Bits, Bit 7-4
#define     FCB_CHLogicBehavKo8Mask 0xF0
#define     FCB_CHLogicBehavKo8Shift 4
#define FCB_CHLogicBehavOut                      9      // 1 Bit, Bit 3
#define     FCB_CHLogicBehavOutMask 0x08
#define     FCB_CHLogicBehavOutShift 3
#define FCB_CHPrioKo0D                           2      // 2 Bits, Bit 7-6
#define     FCB_CHPrioKo0DMask 0xC0
#define     FCB_CHPrioKo0DShift 6
#define FCB_CHPrioKo1D                           2      // 2 Bits, Bit 5-4
#define     FCB_CHPrioKo1DMask 0x30
#define     FCB_CHPrioKo1DShift 4
#define FCB_CHPrioKo2D                           2      // 2 Bits, Bit 3-2
#define     FCB_CHPrioKo2DMask 0x0C
#define     FCB_CHPrioKo2DShift 2
#define FCB_CHPrioKo3D                           2      // 2 Bits, Bit 1-0
#define     FCB_CHPrioKo3DMask 0x03
#define     FCB_CHPrioKo3DShift 0
#define FCB_CHPrioKo4D                           3      // 2 Bits, Bit 7-6
#define     FCB_CHPrioKo4DMask 0xC0
#define     FCB_CHPrioKo4DShift 6
#define FCB_CHPrioKo5D                           3      // 2 Bits, Bit 5-4
#define     FCB_CHPrioKo5DMask 0x30
#define     FCB_CHPrioKo5DShift 4
#define FCB_CHPrioKo6D                           3      // 2 Bits, Bit 3-2
#define     FCB_CHPrioKo6DMask 0x0C
#define     FCB_CHPrioKo6DShift 2
#define FCB_CHPrioKo7D                           3      // 2 Bits, Bit 1-0
#define     FCB_CHPrioKo7DMask 0x03
#define     FCB_CHPrioKo7DShift 0
#define FCB_CHPrioKo8D                           4      // 2 Bits, Bit 7-6
#define     FCB_CHPrioKo8DMask 0xC0
#define     FCB_CHPrioKo8DShift 6
#define FCB_CHPrioOutputType                     4      // 2 Bits, Bit 5-4
#define     FCB_CHPrioOutputTypeMask 0x30
#define     FCB_CHPrioOutputTypeShift 4
#define FCB_CHPrioOutPKo0                        5      // uint8_t
#define FCB_CHPrioOutByteKo0                     5      // uint8_t
#define FCB_CHPrioOutPKo1                        6      // uint8_t
#define FCB_CHPrioOutByteKo1                     6      // uint8_t
#define FCB_CHPrioOutPKo2                        7      // uint8_t
#define FCB_CHPrioOutByteKo2                     7      // uint8_t
#define FCB_CHPrioOutPKo3                        8      // uint8_t
#define FCB_CHPrioOutByteKo3                     8      // uint8_t
#define FCB_CHPrioOutPKo4                        9      // uint8_t
#define FCB_CHPrioOutByteKo4                     9      // uint8_t
#define FCB_CHPrioOutPKo5                       10      // uint8_t
#define FCB_CHPrioOutByteKo5                    10      // uint8_t
#define FCB_CHPrioOutPKo6                       11      // uint8_t
#define FCB_CHPrioOutByteKo6                    11      // uint8_t
#define FCB_CHPrioOutPKo7                       12      // uint8_t
#define FCB_CHPrioOutByteKo7                    12      // uint8_t
#define FCB_CHPrioOutPKo8                       13      // uint8_t
#define FCB_CHPrioOutByteKo8                    13      // uint8_t
#define FCB_CHPrioOutPDefault                   14      // uint8_t
#define FCB_CHPrioOutByteDefault                14      // uint8_t
#define FCB_CHPrioBehavKo0                      15      // 4 Bits, Bit 7-4
#define     FCB_CHPrioBehavKo0Mask 0xF0
#define     FCB_CHPrioBehavKo0Shift 4
#define FCB_CHPrioBehavKo1                      15      // 4 Bits, Bit 3-0
#define     FCB_CHPrioBehavKo1Mask 0x0F
#define     FCB_CHPrioBehavKo1Shift 0
#define FCB_CHPrioBehavKo2                      16      // 4 Bits, Bit 7-4
#define     FCB_CHPrioBehavKo2Mask 0xF0
#define     FCB_CHPrioBehavKo2Shift 4
#define FCB_CHPrioBehavKo3                      16      // 4 Bits, Bit 3-0
#define     FCB_CHPrioBehavKo3Mask 0x0F
#define     FCB_CHPrioBehavKo3Shift 0
#define FCB_CHPrioBehavKo4                      17      // 4 Bits, Bit 7-4
#define     FCB_CHPrioBehavKo4Mask 0xF0
#define     FCB_CHPrioBehavKo4Shift 4
#define FCB_CHPrioBehavKo5                      17      // 4 Bits, Bit 3-0
#define     FCB_CHPrioBehavKo5Mask 0x0F
#define     FCB_CHPrioBehavKo5Shift 0
#define FCB_CHPrioBehavKo6                      18      // 4 Bits, Bit 7-4
#define     FCB_CHPrioBehavKo6Mask 0xF0
#define     FCB_CHPrioBehavKo6Shift 4
#define FCB_CHPrioBehavKo7                      18      // 4 Bits, Bit 3-0
#define     FCB_CHPrioBehavKo7Mask 0x0F
#define     FCB_CHPrioBehavKo7Shift 0
#define FCB_CHPrioBehavKo8                      19      // 4 Bits, Bit 7-4
#define     FCB_CHPrioBehavKo8Mask 0xF0
#define     FCB_CHPrioBehavKo8Shift 4
#define FCB_CHPrioBehavOut                      19      // 1 Bit, Bit 3
#define     FCB_CHPrioBehavOutMask 0x08
#define     FCB_CHPrioBehavOutShift 3
#define FCB_CHAggWeight                          2      // 1 Bit, Bit 7
#define     FCB_CHAggWeightMask 0x80
#define     FCB_CHAggWeightShift 7
#define FCB_CHAggType                            2      // 7 Bits, Bit 6-0
#define     FCB_CHAggTypeMask 0x7F
#define     FCB_CHAggTypeShift 0
#define FCB_CHAggKo0D                            3      // 2 Bits, Bit 7-6
#define     FCB_CHAggKo0DMask 0xC0
#define     FCB_CHAggKo0DShift 6
#define FCB_CHAggKo1D                            3      // 2 Bits, Bit 5-4
#define     FCB_CHAggKo1DMask 0x30
#define     FCB_CHAggKo1DShift 4
#define FCB_CHAggKo2D                            3      // 2 Bits, Bit 3-2
#define     FCB_CHAggKo2DMask 0x0C
#define     FCB_CHAggKo2DShift 2
#define FCB_CHAggKo3D                            3      // 2 Bits, Bit 1-0
#define     FCB_CHAggKo3DMask 0x03
#define     FCB_CHAggKo3DShift 0
#define FCB_CHAggKo4D                            4      // 2 Bits, Bit 7-6
#define     FCB_CHAggKo4DMask 0xC0
#define     FCB_CHAggKo4DShift 6
#define FCB_CHAggKo5D                            4      // 2 Bits, Bit 5-4
#define     FCB_CHAggKo5DMask 0x30
#define     FCB_CHAggKo5DShift 4
#define FCB_CHAggKo6D                            4      // 2 Bits, Bit 3-2
#define     FCB_CHAggKo6DMask 0x0C
#define     FCB_CHAggKo6DShift 2
#define FCB_CHAggKo7D                            4      // 2 Bits, Bit 1-0
#define     FCB_CHAggKo7DMask 0x03
#define     FCB_CHAggKo7DShift 0
#define FCB_CHAggKo8D                            5      // 2 Bits, Bit 7-6
#define     FCB_CHAggKo8DMask 0xC0
#define     FCB_CHAggKo8DShift 6
#define FCB_CHAggBehavOut                        5      // 1 Bit, Bit 5
#define     FCB_CHAggBehavOutMask 0x20
#define     FCB_CHAggBehavOutShift 5
#define FCB_CHAggOutputRounding                  5      // 1 Bit, Bit 3
#define     FCB_CHAggOutputRoundingMask 0x08
#define     FCB_CHAggOutputRoundingShift 3
#define FCB_CHAggOutputOverflow                  5      // 2 Bits, Bit 2-1
#define     FCB_CHAggOutputOverflowMask 0x06
#define     FCB_CHAggOutputOverflowShift 1
#define FCB_CHAggInputDpt                        6      // 8 Bits, Bit 7-0
#define FCB_CHAggOutputDptEff                    7      // 8 Bits, Bit 7-0
#define FCB_CHAggKo0W                            8      // int8_t
#define FCB_CHAggKo1W                            9      // int8_t
#define FCB_CHAggKo2W                           10      // int8_t
#define FCB_CHAggKo3W                           11      // int8_t
#define FCB_CHAggKo4W                           12      // int8_t
#define FCB_CHAggKo5W                           13      // int8_t
#define FCB_CHAggKo6W                           14      // int8_t
#define FCB_CHAggKo7W                           15      // int8_t
#define FCB_CHAggKo8W                           16      // int8_t
#define FCB_CHCountDownTimeStartKo               2      // 4 Bits, Bit 7-4
#define     FCB_CHCountDownTimeStartKoMask 0xF0
#define     FCB_CHCountDownTimeStartKoShift 4
#define FCB_CHCountDownDelayBase                 3      // 2 Bits, Bit 7-6
#define     FCB_CHCountDownDelayBaseMask 0xC0
#define     FCB_CHCountDownDelayBaseShift 6
#define FCB_CHCountDownDelayTime                 3      // 14 Bits, Bit 13-0
#define     FCB_CHCountDownDelayTimeMask 0x3FFF
#define     FCB_CHCountDownDelayTimeShift 0
#define FCB_CHCountDownTimeOffset                5      // 4 Bits, Bit 7-4
#define     FCB_CHCountDownTimeOffsetMask 0xF0
#define     FCB_CHCountDownTimeOffsetShift 4
#define FCB_CHCountDownTrigger                   5      // 4 Bits, Bit 3-0
#define     FCB_CHCountDownTriggerMask 0x0F
#define     FCB_CHCountDownTriggerShift 0
#define FCB_CHCountDownTemplate                  6      // char*, 14 Byte
#define FCB_CHCountDownTemplate1h               21      // char*, 14 Byte
#define FCB_CHCountDownTemplate1m               36      // char*, 14 Byte
#define FCB_CHCountDownTemplateEnd              51      // char*, 14 Byte
#define FCB_CHCountDownTextPause                66      // char*, 1 Byte
#define FCB_CHCountDownTextRun                  68      // char*, 1 Byte
#define FCB_CHCountDownCounterKo                70      // 4 Bits, Bit 7-4
#define     FCB_CHCountDownCounterKoMask 0xF0
#define     FCB_CHCountDownCounterKoShift 4
#define FCB_CHCountDownTextKo                   70      // 2 Bits, Bit 3-2
#define     FCB_CHCountDownTextKoMask 0x0C
#define     FCB_CHCountDownTextKoShift 2
#define FCB_CHMonitoringValueType                2      // 8 Bits, Bit 7-0
#define FCB_CHMonitoringWDEnabled                3      // 1 Bit, Bit 7
#define     FCB_CHMonitoringWDEnabledMask 0x80
#define     FCB_CHMonitoringWDEnabledShift 7
#define FCB_CHMonitoringWDTTimeoutDelayBase      4      // 2 Bits, Bit 7-6
#define     FCB_CHMonitoringWDTTimeoutDelayBaseMask 0xC0
#define     FCB_CHMonitoringWDTTimeoutDelayBaseShift 6
#define FCB_CHMonitoringWDTTimeoutDelayTime      4      // 14 Bits, Bit 13-0
#define     FCB_CHMonitoringWDTTimeoutDelayTimeMask 0x3FFF
#define     FCB_CHMonitoringWDTTimeoutDelayTimeShift 0
#define FCB_CHMonitoringWDBehavior               6      // 4 Bits, Bit 7-4
#define     FCB_CHMonitoringWDBehaviorMask 0xF0
#define     FCB_CHMonitoringWDBehaviorShift 4
#define FCB_CHMonitoringWDDpt1                   7      // 8 Bits, Bit 7-0
#define FCB_CHMonitoringWDDpt5                   7      // uint8_t
#define FCB_CHMonitoringWDDpt5001                7      // uint8_t
#define FCB_CHMonitoringWDDpt6                   7      // int8_t
#define FCB_CHMonitoringWDDpt7                   7      // uint16_t
#define FCB_CHMonitoringWDDpt8                   7      // int16_t
#define FCB_CHMonitoringWDDpt9                   7      // float
#define FCB_CHMonitoringWDDpt12                  7      // uint32_t
#define FCB_CHMonitoringWDDpt13                  7      // int32_t
#define FCB_CHMonitoringWDDpt14                  7      // float
#define FCB_CHMonitoringWDDpt16                  7      // char*, 14 Byte
#define FCB_CHMonitoringMin                     22      // 4 Bits, Bit 7-4
#define     FCB_CHMonitoringMinMask 0xF0
#define     FCB_CHMonitoringMinShift 4
#define FCB_CHMonitoringMinDpt1                 23      // 1 Bit, Bit 7
#define     FCB_CHMonitoringMinDpt1Mask 0x80
#define     FCB_CHMonitoringMinDpt1Shift 7
#define FCB_CHMonitoringMinDpt5                 23      // uint8_t
#define FCB_CHMonitoringMinDpt5001              23      // uint8_t
#define FCB_CHMonitoringMinDpt6                 23      // int8_t
#define FCB_CHMonitoringMinDpt7                 23      // uint16_t
#define FCB_CHMonitoringMinDpt8                 23      // int16_t
#define FCB_CHMonitoringMinDpt9                 23      // float
#define FCB_CHMonitoringMinDpt12                23      // uint32_t
#define FCB_CHMonitoringMinDpt13                23      // int32_t
#define FCB_CHMonitoringMinDpt14                23      // float
#define FCB_CHMonitoringMax                     27      // 4 Bits, Bit 7-4
#define     FCB_CHMonitoringMaxMask 0xF0
#define     FCB_CHMonitoringMaxShift 4
#define FCB_CHMonitoringMaxDpt1                 28      // 1 Bit, Bit 7
#define     FCB_CHMonitoringMaxDpt1Mask 0x80
#define     FCB_CHMonitoringMaxDpt1Shift 7
#define FCB_CHMonitoringMaxDpt5                 28      // uint8_t
#define FCB_CHMonitoringMaxDpt5001              28      // uint8_t
#define FCB_CHMonitoringMaxDpt6                 28      // int8_t
#define FCB_CHMonitoringMaxDpt7                 28      // uint16_t
#define FCB_CHMonitoringMaxDpt8                 28      // int16_t
#define FCB_CHMonitoringMaxDpt9                 28      // float
#define FCB_CHMonitoringMaxDpt12                28      // uint32_t
#define FCB_CHMonitoringMaxDpt13                28      // int32_t
#define FCB_CHMonitoringMaxDpt14                28      // float
#define FCB_CHMonitoringOutput                  32      // 4 Bits, Bit 7-4
#define     FCB_CHMonitoringOutputMask 0xF0
#define     FCB_CHMonitoringOutputShift 4
#define FCB_CHSelectionValueType                 2      // 8 Bits, Bit 7-0
#define FCB_CHSelectionType                      3      // 8 Bits, Bit 7-0
#define FCB_CHSelectionSwitching                 4      // 4 Bits, Bit 7-4
#define     FCB_CHSelectionSwitchingMask 0xF0
#define     FCB_CHSelectionSwitchingShift 4
#define FCB_CHSelectionStateOutput               4      // 1 Bit, Bit 3
#define     FCB_CHSelectionStateOutputMask 0x08
#define     FCB_CHSelectionStateOutputShift 3
#define FCB_CHBlinkerOnDelayBase                 4      // 2 Bits, Bit 7-6
#define     FCB_CHBlinkerOnDelayBaseMask 0xC0
#define     FCB_CHBlinkerOnDelayBaseShift 6
#define FCB_CHBlinkerOnDelayTime                 4      // 14 Bits, Bit 13-0
#define     FCB_CHBlinkerOnDelayTimeMask 0x3FFF
#define     FCB_CHBlinkerOnDelayTimeShift 0
#define FCB_CHBlinkerOffDelayBase                6      // 2 Bits, Bit 7-6
#define     FCB_CHBlinkerOffDelayBaseMask 0xC0
#define     FCB_CHBlinkerOffDelayBaseShift 6
#define FCB_CHBlinkerOffDelayTime                6      // 14 Bits, Bit 13-0
#define     FCB_CHBlinkerOffDelayTimeMask 0x3FFF
#define     FCB_CHBlinkerOffDelayTimeShift 0
#define FCB_CHBlinkerStart                       8      // 4 Bits, Bit 7-4
#define     FCB_CHBlinkerStartMask 0xF0
#define     FCB_CHBlinkerStartShift 4
#define FCB_CHBlinkerStop                        8      // 4 Bits, Bit 3-0
#define     FCB_CHBlinkerStopMask 0x0F
#define     FCB_CHBlinkerStopShift 0
#define FCB_CHBlinkerBreak                       9      // 4 Bits, Bit 7-4
#define     FCB_CHBlinkerBreakMask 0xF0
#define     FCB_CHBlinkerBreakShift 4
#define FCB_CHBlinkerBreakWithoutBreak           9      // 4 Bits, Bit 7-4
#define     FCB_CHBlinkerBreakWithoutBreakMask 0xF0
#define     FCB_CHBlinkerBreakWithoutBreakShift 4
#define FCB_CHBlinkerOutputDpt                   9      // 8 Bits, Bit 3--4
#define FCB_CHBlinkerOnPercentage               10      // uint8_t
#define FCB_CHBlinkerOffPercentage              11      // uint8_t
#define FCB_CHBlinkerCount                      12      // 8 Bits, Bit 7-0
#define FCB_CHBlinkerStartAnzahl                13      // 1 Bit, Bit 7
#define     FCB_CHBlinkerStartAnzahlMask 0x80
#define     FCB_CHBlinkerStartAnzahlShift 7

// Type
#define ParamFCB_CHChannelType                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHChannelType)))
// Kanal deaktivieren (zu Testzwecken)
#define ParamFCB_CHChannelDisabled                   ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHChannelDisabled)) & FCB_CHChannelDisabledMask))
// Eingang 1
#define ParamFCB_CHLogicKo0D                         ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo0D)) & FCB_CHLogicKo0DMask) >> FCB_CHLogicKo0DShift)
// Eingang 2
#define ParamFCB_CHLogicKo1D                         ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo1D)) & FCB_CHLogicKo1DMask) >> FCB_CHLogicKo1DShift)
// Eingang 3
#define ParamFCB_CHLogicKo2D                         ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo2D)) & FCB_CHLogicKo2DMask) >> FCB_CHLogicKo2DShift)
// Eingang 4
#define ParamFCB_CHLogicKo3D                         (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo3D)) & FCB_CHLogicKo3DMask)
// Eingang 5
#define ParamFCB_CHLogicKo4D                         ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo4D)) & FCB_CHLogicKo4DMask) >> FCB_CHLogicKo4DShift)
// Eingang 6
#define ParamFCB_CHLogicKo5D                         ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo5D)) & FCB_CHLogicKo5DMask) >> FCB_CHLogicKo5DShift)
// Eingang 7
#define ParamFCB_CHLogicKo6D                         ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo6D)) & FCB_CHLogicKo6DMask) >> FCB_CHLogicKo6DShift)
// Eingang 8
#define ParamFCB_CHLogicKo7D                         (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo7D)) & FCB_CHLogicKo7DMask)
// Eingang 9
#define ParamFCB_CHLogicKo8D                         ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo8D)) & FCB_CHLogicKo8DMask) >> FCB_CHLogicKo8DShift)
// Eingang 10
#define ParamFCB_CHLogicKo9D                         ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicKo9D)) & FCB_CHLogicKo9DMask) >> FCB_CHLogicKo9DShift)
// Invertiert
#define ParamFCB_CHLogicOutInv                       ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicOutInv)) & FCB_CHLogicOutInvMask))
// Initialisierung
#define ParamFCB_CHLogicBehavKo0                     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo0)) & FCB_CHLogicBehavKo0Mask) >> FCB_CHLogicBehavKo0Shift)
// Initialisierung
#define ParamFCB_CHLogicBehavKo1                     (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo1)) & FCB_CHLogicBehavKo1Mask)
// Initialisierung
#define ParamFCB_CHLogicBehavKo2                     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo2)) & FCB_CHLogicBehavKo2Mask) >> FCB_CHLogicBehavKo2Shift)
// Initialisierung
#define ParamFCB_CHLogicBehavKo3                     (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo3)) & FCB_CHLogicBehavKo3Mask)
// Initialisierung
#define ParamFCB_CHLogicBehavKo4                     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo4)) & FCB_CHLogicBehavKo4Mask) >> FCB_CHLogicBehavKo4Shift)
// Initialisierung
#define ParamFCB_CHLogicBehavKo5                     (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo5)) & FCB_CHLogicBehavKo5Mask)
// Initialisierung
#define ParamFCB_CHLogicBehavKo6                     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo6)) & FCB_CHLogicBehavKo6Mask) >> FCB_CHLogicBehavKo6Shift)
// Initialisierung
#define ParamFCB_CHLogicBehavKo7                     (knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo7)) & FCB_CHLogicBehavKo7Mask)
// Initialisierung
#define ParamFCB_CHLogicBehavKo8                     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavKo8)) & FCB_CHLogicBehavKo8Mask) >> FCB_CHLogicBehavKo8Shift)
// Sendeverhalten
#define ParamFCB_CHLogicBehavOut                     ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHLogicBehavOut)) & FCB_CHLogicBehavOutMask))
// Eingang 1
#define ParamFCB_CHPrioKo0D                          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo0D)) & FCB_CHPrioKo0DMask) >> FCB_CHPrioKo0DShift)
// Eingang 2
#define ParamFCB_CHPrioKo1D                          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo1D)) & FCB_CHPrioKo1DMask) >> FCB_CHPrioKo1DShift)
// Eingang 3
#define ParamFCB_CHPrioKo2D                          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo2D)) & FCB_CHPrioKo2DMask) >> FCB_CHPrioKo2DShift)
// Eingang 4
#define ParamFCB_CHPrioKo3D                          (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo3D)) & FCB_CHPrioKo3DMask)
// Eingang 5
#define ParamFCB_CHPrioKo4D                          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo4D)) & FCB_CHPrioKo4DMask) >> FCB_CHPrioKo4DShift)
// Eingang 6
#define ParamFCB_CHPrioKo5D                          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo5D)) & FCB_CHPrioKo5DMask) >> FCB_CHPrioKo5DShift)
// Eingang 7
#define ParamFCB_CHPrioKo6D                          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo6D)) & FCB_CHPrioKo6DMask) >> FCB_CHPrioKo6DShift)
// Eingang 8
#define ParamFCB_CHPrioKo7D                          (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo7D)) & FCB_CHPrioKo7DMask)
// Eingang 9
#define ParamFCB_CHPrioKo8D                          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioKo8D)) & FCB_CHPrioKo8DMask) >> FCB_CHPrioKo8DShift)
// Type
#define ParamFCB_CHPrioOutputType                    ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutputType)) & FCB_CHPrioOutputTypeMask) >> FCB_CHPrioOutputTypeShift)
// Ausgangswert
#define ParamFCB_CHPrioOutPKo0                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo0)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo0                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo0)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo1                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo1)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo1                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo1)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo2                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo2)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo2                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo2)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo3                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo3)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo3                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo3)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo4                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo4)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo4                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo4)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo5                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo5)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo5                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo5)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo6                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo6)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo6                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo6)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo7                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo7)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo7                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo7)))
// Ausgangswert
#define ParamFCB_CHPrioOutPKo8                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPKo8)))
// Ausgangswert
#define ParamFCB_CHPrioOutByteKo8                    (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteKo8)))
// Ausgangswert wenn alle Eingänge AUS
#define ParamFCB_CHPrioOutPDefault                   (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutPDefault)))
// Ausgangswert wenn alle Eingänge AUS
#define ParamFCB_CHPrioOutByteDefault                (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioOutByteDefault)))
// Initialisierung
#define ParamFCB_CHPrioBehavKo0                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo0)) & FCB_CHPrioBehavKo0Mask) >> FCB_CHPrioBehavKo0Shift)
// Initialisierung
#define ParamFCB_CHPrioBehavKo1                      (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo1)) & FCB_CHPrioBehavKo1Mask)
// Initialisierung
#define ParamFCB_CHPrioBehavKo2                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo2)) & FCB_CHPrioBehavKo2Mask) >> FCB_CHPrioBehavKo2Shift)
// Initialisierung
#define ParamFCB_CHPrioBehavKo3                      (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo3)) & FCB_CHPrioBehavKo3Mask)
// Initialisierung
#define ParamFCB_CHPrioBehavKo4                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo4)) & FCB_CHPrioBehavKo4Mask) >> FCB_CHPrioBehavKo4Shift)
// Initialisierung
#define ParamFCB_CHPrioBehavKo5                      (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo5)) & FCB_CHPrioBehavKo5Mask)
// Initialisierung
#define ParamFCB_CHPrioBehavKo6                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo6)) & FCB_CHPrioBehavKo6Mask) >> FCB_CHPrioBehavKo6Shift)
// Initialisierung
#define ParamFCB_CHPrioBehavKo7                      (knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo7)) & FCB_CHPrioBehavKo7Mask)
// Initialisierung
#define ParamFCB_CHPrioBehavKo8                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavKo8)) & FCB_CHPrioBehavKo8Mask) >> FCB_CHPrioBehavKo8Shift)
// Sendeverhalten
#define ParamFCB_CHPrioBehavOut                      ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHPrioBehavOut)) & FCB_CHPrioBehavOutMask))
// Gewichtung der Eingänge
#define ParamFCB_CHAggWeight                         ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggWeight)) & FCB_CHAggWeightMask))
// Funktion
#define ParamFCB_CHAggType                           (knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggType)) & FCB_CHAggTypeMask)
// Eingang 1
#define ParamFCB_CHAggKo0D                           ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo0D)) & FCB_CHAggKo0DMask) >> FCB_CHAggKo0DShift)
// Eingang 2
#define ParamFCB_CHAggKo1D                           ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo1D)) & FCB_CHAggKo1DMask) >> FCB_CHAggKo1DShift)
// Eingang 3
#define ParamFCB_CHAggKo2D                           ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo2D)) & FCB_CHAggKo2DMask) >> FCB_CHAggKo2DShift)
// Eingang 4
#define ParamFCB_CHAggKo3D                           (knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo3D)) & FCB_CHAggKo3DMask)
// Eingang 5
#define ParamFCB_CHAggKo4D                           ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo4D)) & FCB_CHAggKo4DMask) >> FCB_CHAggKo4DShift)
// Eingang 6
#define ParamFCB_CHAggKo5D                           ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo5D)) & FCB_CHAggKo5DMask) >> FCB_CHAggKo5DShift)
// Eingang 7
#define ParamFCB_CHAggKo6D                           ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo6D)) & FCB_CHAggKo6DMask) >> FCB_CHAggKo6DShift)
// Eingang 8
#define ParamFCB_CHAggKo7D                           (knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo7D)) & FCB_CHAggKo7DMask)
// Eingang 9
#define ParamFCB_CHAggKo8D                           ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo8D)) & FCB_CHAggKo8DMask) >> FCB_CHAggKo8DShift)
// Sendeverhalten
#define ParamFCB_CHAggBehavOut                       ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggBehavOut)) & FCB_CHAggBehavOutMask))
// Rundungsmodus
#define ParamFCB_CHAggOutputRounding                 ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggOutputRounding)) & FCB_CHAggOutputRoundingMask))
// Bei Überschreiten des Wertebereichs
#define ParamFCB_CHAggOutputOverflow                 ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggOutputOverflow)) & FCB_CHAggOutputOverflowMask) >> FCB_CHAggOutputOverflowShift)
// Wertetype / DPT
#define ParamFCB_CHAggInputDpt                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggInputDpt)))
// DPT Ausgang
#define ParamFCB_CHAggOutputDptEff                   (knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggOutputDptEff)))
// Gewicht Eingang 1
#define ParamFCB_CHAggKo0W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo0W)))
// Gewicht Eingang 2
#define ParamFCB_CHAggKo1W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo1W)))
// Gewicht Eingang 3
#define ParamFCB_CHAggKo2W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo2W)))
// Gewicht Eingang 4
#define ParamFCB_CHAggKo3W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo3W)))
// Gewicht Eingang 5
#define ParamFCB_CHAggKo4W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo4W)))
// Gewicht Eingang 6
#define ParamFCB_CHAggKo5W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo5W)))
// Gewicht Eingang 7
#define ParamFCB_CHAggKo6W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo6W)))
// Gewicht Eingang 8
#define ParamFCB_CHAggKo7W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo7W)))
// Gewicht Eingang 9
#define ParamFCB_CHAggKo8W                           ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHAggKo8W)))
// Start mit Zeit
#define ParamFCB_CHCountDownTimeStartKo              ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHCountDownTimeStartKo)) & FCB_CHCountDownTimeStartKoMask) >> FCB_CHCountDownTimeStartKoShift)
// Ablaufzeit Einheit
#define ParamFCB_CHCountDownDelayBase                ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHCountDownDelayBase)) & FCB_CHCountDownDelayBaseMask) >> FCB_CHCountDownDelayBaseShift)
// Ablaufzeit
#define ParamFCB_CHCountDownDelayTime                (knx.paramWord(FCB_ParamCalcIndex(FCB_CHCountDownDelayTime)) & FCB_CHCountDownDelayTimeMask)
// Ablaufzeit (in Millisekunden)
#define ParamFCB_CHCountDownDelayTimeMS              (paramDelay(knx.paramWord(FCB_ParamCalcIndex(FCB_CHCountDownDelayTime))))
// Laufzeit Verringern / Erhöhen
#define ParamFCB_CHCountDownTimeOffset               ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHCountDownTimeOffset)) & FCB_CHCountDownTimeOffsetMask) >> FCB_CHCountDownTimeOffsetShift)
// Auslöser / Ende
#define ParamFCB_CHCountDownTrigger                  (knx.paramByte(FCB_ParamCalcIndex(FCB_CHCountDownTrigger)) & FCB_CHCountDownTriggerMask)
// Standard
#define ParamFCB_CHCountDownTemplate                 (knx.paramData(FCB_ParamCalcIndex(FCB_CHCountDownTemplate)))
// kleiner eine Stunde
#define ParamFCB_CHCountDownTemplate1h               (knx.paramData(FCB_ParamCalcIndex(FCB_CHCountDownTemplate1h)))
// kleiner eine Minute
#define ParamFCB_CHCountDownTemplate1m               (knx.paramData(FCB_ParamCalcIndex(FCB_CHCountDownTemplate1m)))
// Ende
#define ParamFCB_CHCountDownTemplateEnd              (knx.paramData(FCB_ParamCalcIndex(FCB_CHCountDownTemplateEnd)))
// Pause
#define ParamFCB_CHCountDownTextPause                (knx.paramData(FCB_ParamCalcIndex(FCB_CHCountDownTextPause)))
// Läuft
#define ParamFCB_CHCountDownTextRun                  (knx.paramData(FCB_ParamCalcIndex(FCB_CHCountDownTextRun)))
// Zähler
#define ParamFCB_CHCountDownCounterKo                ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHCountDownCounterKo)) & FCB_CHCountDownCounterKoMask) >> FCB_CHCountDownCounterKoShift)
// Text
#define ParamFCB_CHCountDownTextKo                   ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHCountDownTextKo)) & FCB_CHCountDownTextKoMask) >> FCB_CHCountDownTextKoShift)
// Werttype
#define ParamFCB_CHMonitoringValueType               (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringValueType)))
// Zeitüberwachung aktiv
#define ParamFCB_CHMonitoringWDEnabled               ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringWDEnabled)) & FCB_CHMonitoringWDEnabledMask))
// Watchdog Zeitbasis
#define ParamFCB_CHMonitoringWDTTimeoutDelayBase     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringWDTTimeoutDelayBase)) & FCB_CHMonitoringWDTTimeoutDelayBaseMask) >> FCB_CHMonitoringWDTTimeoutDelayBaseShift)
// Watchdog Zeit
#define ParamFCB_CHMonitoringWDTTimeoutDelayTime     (knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringWDTTimeoutDelayTime)) & FCB_CHMonitoringWDTTimeoutDelayTimeMask)
// Watchdog Zeit (in Millisekunden)
#define ParamFCB_CHMonitoringWDTTimeoutDelayTimeMS   (paramDelay(knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringWDTTimeoutDelayTime))))
// Verhalten bei Zeitüberschreitung
#define ParamFCB_CHMonitoringWDBehavior              ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringWDBehavior)) & FCB_CHMonitoringWDBehaviorMask) >> FCB_CHMonitoringWDBehaviorShift)
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt1                  (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt1)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt5                  (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt5)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt5001               (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt5001)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt6                  ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt6)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt7                  (knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt7)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt8                  ((int16_t)knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt8)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt9                  (knx.paramFloat(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt9), Float_Enc_IEEE754Single))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt12                 (knx.paramInt(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt12)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt13                 ((int32_t)knx.paramInt(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt13)))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt14                 (knx.paramFloat(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt14), Float_Enc_IEEE754Single))
// Ersatzwert
#define ParamFCB_CHMonitoringWDDpt16                 (knx.paramData(FCB_ParamCalcIndex(FCB_CHMonitoringWDDpt16)))
// Verhalten bei Wertunterschreitung
#define ParamFCB_CHMonitoringMin                     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMin)) & FCB_CHMonitoringMinMask) >> FCB_CHMonitoringMinShift)
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt1                 ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt1)) & FCB_CHMonitoringMinDpt1Mask))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt5                 (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt5)))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt5001              (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt5001)))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt6                 ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt6)))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt7                 (knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt7)))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt8                 ((int16_t)knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt8)))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt9                 (knx.paramFloat(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt9), Float_Enc_IEEE754Single))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt12                (knx.paramInt(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt12)))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt13                ((int32_t)knx.paramInt(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt13)))
// Minimaler zulässiger Wert
#define ParamFCB_CHMonitoringMinDpt14                (knx.paramFloat(FCB_ParamCalcIndex(FCB_CHMonitoringMinDpt14), Float_Enc_IEEE754Single))
// Verhalten bei Wertüberschreitung
#define ParamFCB_CHMonitoringMax                     ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMax)) & FCB_CHMonitoringMaxMask) >> FCB_CHMonitoringMaxShift)
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt1                 ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt1)) & FCB_CHMonitoringMaxDpt1Mask))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt5                 (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt5)))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt5001              (knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt5001)))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt6                 ((int8_t)knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt6)))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt7                 (knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt7)))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt8                 ((int16_t)knx.paramWord(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt8)))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt9                 (knx.paramFloat(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt9), Float_Enc_IEEE754Single))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt12                (knx.paramInt(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt12)))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt13                ((int32_t)knx.paramInt(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt13)))
// Maximaler zulässiger Wert
#define ParamFCB_CHMonitoringMaxDpt14                (knx.paramFloat(FCB_ParamCalcIndex(FCB_CHMonitoringMaxDpt14), Float_Enc_IEEE754Single))
// Sendeverhalten
#define ParamFCB_CHMonitoringOutput                  ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHMonitoringOutput)) & FCB_CHMonitoringOutputMask) >> FCB_CHMonitoringOutputShift)
// Datentype
#define ParamFCB_CHSelectionValueType                (knx.paramByte(FCB_ParamCalcIndex(FCB_CHSelectionValueType)))
// Anzahl und Typ der Auswahlen (mit gemeinsamen Auswahl-Eingang)
#define ParamFCB_CHSelectionType                     (knx.paramByte(FCB_ParamCalcIndex(FCB_CHSelectionType)))
// Bei Umschaltung
#define ParamFCB_CHSelectionSwitching                ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHSelectionSwitching)) & FCB_CHSelectionSwitchingMask) >> FCB_CHSelectionSwitchingShift)
// Auswahl Status Objekt
#define ParamFCB_CHSelectionStateOutput              ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHSelectionStateOutput)) & FCB_CHSelectionStateOutputMask))
// Blinker EIN Zeitbasis
#define ParamFCB_CHBlinkerOnDelayBase                ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerOnDelayBase)) & FCB_CHBlinkerOnDelayBaseMask) >> FCB_CHBlinkerOnDelayBaseShift)
// Blinker EIN Zeit
#define ParamFCB_CHBlinkerOnDelayTime                (knx.paramWord(FCB_ParamCalcIndex(FCB_CHBlinkerOnDelayTime)) & FCB_CHBlinkerOnDelayTimeMask)
// Blinker EIN Zeit (in Millisekunden)
#define ParamFCB_CHBlinkerOnDelayTimeMS              (paramDelay(knx.paramWord(FCB_ParamCalcIndex(FCB_CHBlinkerOnDelayTime))))
// Blinker AUS Zeitbasis
#define ParamFCB_CHBlinkerOffDelayBase               ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerOffDelayBase)) & FCB_CHBlinkerOffDelayBaseMask) >> FCB_CHBlinkerOffDelayBaseShift)
// Blinker AUS Zeit
#define ParamFCB_CHBlinkerOffDelayTime               (knx.paramWord(FCB_ParamCalcIndex(FCB_CHBlinkerOffDelayTime)) & FCB_CHBlinkerOffDelayTimeMask)
// Blinker AUS Zeit (in Millisekunden)
#define ParamFCB_CHBlinkerOffDelayTimeMS             (paramDelay(knx.paramWord(FCB_ParamCalcIndex(FCB_CHBlinkerOffDelayTime))))
// Start
#define ParamFCB_CHBlinkerStart                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerStart)) & FCB_CHBlinkerStartMask) >> FCB_CHBlinkerStartShift)
// Ende
#define ParamFCB_CHBlinkerStop                       (knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerStop)) & FCB_CHBlinkerStopMask)
// AUS Telegram am 'Start' Eingang
#define ParamFCB_CHBlinkerBreak                      ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerBreak)) & FCB_CHBlinkerBreakMask) >> FCB_CHBlinkerBreakShift)
// AUS Telegram am 'Start' Eingang
#define ParamFCB_CHBlinkerBreakWithoutBreak          ((knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerBreakWithoutBreak)) & FCB_CHBlinkerBreakWithoutBreakMask) >> FCB_CHBlinkerBreakWithoutBreakShift)
// Ausgang
#define ParamFCB_CHBlinkerOutputDpt                  (knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerOutputDpt)))
// Wert für EIN
#define ParamFCB_CHBlinkerOnPercentage               (knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerOnPercentage)))
// Wert für AUS
#define ParamFCB_CHBlinkerOffPercentage              (knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerOffPercentage)))
// Anzahl der Blinkvorgänge
#define ParamFCB_CHBlinkerCount                      (knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerCount)))
// Objekt zum Starten mit Anzahl
#define ParamFCB_CHBlinkerStartAnzahl                ((bool)(knx.paramByte(FCB_ParamCalcIndex(FCB_CHBlinkerStartAnzahl)) & FCB_CHBlinkerStartAnzahlMask))

// deprecated
#define FCB_KoOffset 250

// Communication objects per channel (multiple occurrence)
#define FCB_KoBlockOffset 250
#define FCB_KoBlockSize 10

#define FCB_KoCalcNumber(index) (index + FCB_KoBlockOffset + _channelIndex * FCB_KoBlockSize)
#define FCB_KoCalcIndex(number) ((number >= FCB_KoCalcNumber(0) && number < FCB_KoCalcNumber(FCB_KoBlockSize)) ? (number - FCB_KoBlockOffset) % FCB_KoBlockSize : -1)
#define FCB_KoCalcChannel(number) ((number >= FCB_KoBlockOffset && number < FCB_KoBlockOffset + FCB_ChannelCount * FCB_KoBlockSize) ? (number - FCB_KoBlockOffset) / FCB_KoBlockSize : -1)

#define FCB_KoCHKO0 0
#define FCB_KoCHKO1 1
#define FCB_KoCHKO2 2
#define FCB_KoCHKO3 3
#define FCB_KoCHKO4 4
#define FCB_KoCHKO5 5
#define FCB_KoCHKO6 6
#define FCB_KoCHKO7 7
#define FCB_KoCHKO8 8
#define FCB_KoCHKO9 9

// 
#define KoFCB_CHKO0                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO0)))
// 
#define KoFCB_CHKO1                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO1)))
// 
#define KoFCB_CHKO2                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO2)))
// 
#define KoFCB_CHKO3                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO3)))
// 
#define KoFCB_CHKO4                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO4)))
// 
#define KoFCB_CHKO5                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO5)))
// 
#define KoFCB_CHKO6                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO6)))
// 
#define KoFCB_CHKO7                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO7)))
// 
#define KoFCB_CHKO8                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO8)))
// 
#define KoFCB_CHKO9                               (knx.getGroupObject(FCB_KoCalcNumber(FCB_KoCHKO9)))

#define BTN_ReactionTimeMultiClick              14272      // 8 Bits, Bit 7-0
#define BTN_ReactionTimeLong                    14273      // 8 Bits, Bit 7-0
#define BTN_ReactionTimeExtraLong               14274      // 8 Bits, Bit 7-0
#define BTN_VisibleChannels                     14275      // uint8_t

// Mehrfach-Klick
#define ParamBTN_ReactionTimeMultiClick              (knx.paramByte(BTN_ReactionTimeMultiClick))
// Langer Tastendruck
#define ParamBTN_ReactionTimeLong                    (knx.paramByte(BTN_ReactionTimeLong))
// Extra langer Tastendruck
#define ParamBTN_ReactionTimeExtraLong               (knx.paramByte(BTN_ReactionTimeExtraLong))
// Verfügbare Kanäle
#define ParamBTN_VisibleChannels                     (knx.paramByte(BTN_VisibleChannels))

#define BTN_ChannelCount 1

// Parameter per channel
#define BTN_ParamBlockOffset 14276
#define BTN_ParamBlockSize 53
#define BTN_ParamCalcIndex(index) (index + BTN_ParamBlockOffset + _channelIndex * BTN_ParamBlockSize)

#define BTN_bMode                                0      // 7 Bits, Bit 7-1
#define     BTN_bModeMask 0xFE
#define     BTN_bModeShift 1
#define BTN_bLock                                1      // 2 Bits, Bit 7-6
#define     BTN_bLockMask 0xC0
#define     BTN_bLockShift 6
#define BTN_bMultiClickCount                     1      // 1 Bit, Bit 7
#define     BTN_bMultiClickCountMask 0x80
#define     BTN_bMultiClickCountShift 7
#define BTN_bDynamicStatus                       1      // 1 Bit, Bit 2
#define     BTN_bDynamicStatusMask 0x04
#define     BTN_bDynamicStatusShift 2
#define BTN_bInA                                 2      // 8 Bits, Bit 7-0
#define BTN_bInB                                 4      // 8 Bits, Bit 7-0
#define BTN_bReactionTimeMultiClick              6      // 8 Bits, Bit 7-0
#define BTN_bReactionTimeLong                    7      // 8 Bits, Bit 7-0
#define BTN_bReactionTimeExtraLong               8      // 8 Bits, Bit 7-0
#define BTN_bOutShort_DPT                        9      // 8 Bits, Bit 7-0
#define BTN_bOutLong_DPT                        10      // 8 Bits, Bit 7-0
#define BTN_bOutExtraLong_DPT                   11      // 8 Bits, Bit 7-0
#define BTN_bOutMulti_DPT                       12      // 8 Bits, Bit 7-0
#define BTN_bOutMulti_Click1_Active             13      // 1 Bit, Bit 7
#define     BTN_bOutMulti_Click1_ActiveMask 0x80
#define     BTN_bOutMulti_Click1_ActiveShift 7
#define BTN_bOutMulti_Click2_Active             13      // 1 Bit, Bit 6
#define     BTN_bOutMulti_Click2_ActiveMask 0x40
#define     BTN_bOutMulti_Click2_ActiveShift 6
#define BTN_bOutMulti_Click3_Active             13      // 1 Bit, Bit 5
#define     BTN_bOutMulti_Click3_ActiveMask 0x20
#define     BTN_bOutMulti_Click3_ActiveShift 5
#define BTN_bOutShort_T1_Active_Press           14      // 1 Bit, Bit 7
#define     BTN_bOutShort_T1_Active_PressMask 0x80
#define     BTN_bOutShort_T1_Active_PressShift 7
#define BTN_bOutShort_T1_Active_Release         14      // 1 Bit, Bit 6
#define     BTN_bOutShort_T1_Active_ReleaseMask 0x40
#define     BTN_bOutShort_T1_Active_ReleaseShift 6
#define BTN_bOutShort_T2_Active_Press           14      // 1 Bit, Bit 5
#define     BTN_bOutShort_T2_Active_PressMask 0x20
#define     BTN_bOutShort_T2_Active_PressShift 5
#define BTN_bOutShort_T2_Active_Release         14      // 1 Bit, Bit 4
#define     BTN_bOutShort_T2_Active_ReleaseMask 0x10
#define     BTN_bOutShort_T2_Active_ReleaseShift 4
#define BTN_bOutLong_T1_Active_Press            15      // 1 Bit, Bit 7
#define     BTN_bOutLong_T1_Active_PressMask 0x80
#define     BTN_bOutLong_T1_Active_PressShift 7
#define BTN_bOutLong_T1_Active_Release          15      // 1 Bit, Bit 6
#define     BTN_bOutLong_T1_Active_ReleaseMask 0x40
#define     BTN_bOutLong_T1_Active_ReleaseShift 6
#define BTN_bOutLong_T2_Active_Press            15      // 1 Bit, Bit 5
#define     BTN_bOutLong_T2_Active_PressMask 0x20
#define     BTN_bOutLong_T2_Active_PressShift 5
#define BTN_bOutLong_T2_Active_Release          15      // 1 Bit, Bit 4
#define     BTN_bOutLong_T2_Active_ReleaseMask 0x10
#define     BTN_bOutLong_T2_Active_ReleaseShift 4
#define BTN_bOutExtraLong_T1_Active_Press       16      // 1 Bit, Bit 7
#define     BTN_bOutExtraLong_T1_Active_PressMask 0x80
#define     BTN_bOutExtraLong_T1_Active_PressShift 7
#define BTN_bOutExtraLong_T1_Active_Release     16      // 1 Bit, Bit 6
#define     BTN_bOutExtraLong_T1_Active_ReleaseMask 0x40
#define     BTN_bOutExtraLong_T1_Active_ReleaseShift 6
#define BTN_bOutExtraLong_T2_Active_Press       16      // 1 Bit, Bit 5
#define     BTN_bOutExtraLong_T2_Active_PressMask 0x20
#define     BTN_bOutExtraLong_T2_Active_PressShift 5
#define BTN_bOutExtraLong_T2_Active_Release     16      // 1 Bit, Bit 4
#define     BTN_bOutExtraLong_T2_Active_ReleaseMask 0x10
#define     BTN_bOutExtraLong_T2_Active_ReleaseShift 4
#define BTN_bOutShort_T1_Dpt1_Press             17      // 16 Bits, Bit 15-0
#define BTN_bOutShort_T1_Dpt1_Release           19      // 16 Bits, Bit 15-0
#define BTN_bOutShort_T2_Dpt1_Press             21      // 16 Bits, Bit 15-0
#define BTN_bOutShort_T2_Dpt1_Release           23      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T1_Dpt1_Press              25      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T1_Dpt1_Release            27      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T2_Dpt1_Press              29      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T2_Dpt1_Release            31      // 16 Bits, Bit 15-0
#define BTN_bOutExtraLong_T1_Dpt1_Press         33      // 16 Bits, Bit 15-0
#define BTN_bOutExtraLong_T1_Dpt1_Release       35      // 16 Bits, Bit 15-0
#define BTN_bOutExtraLong_T2_Dpt1_Press         37      // 16 Bits, Bit 15-0
#define BTN_bOutExtraLong_T2_Dpt1_Release       39      // 16 Bits, Bit 15-0
#define BTN_bOutMulti_Click1_Dpt1               41      // 16 Bits, Bit 15-0
#define BTN_bOutMulti_Click2_Dpt1               43      // 16 Bits, Bit 15-0
#define BTN_bOutMulti_Click3_Dpt1               45      // 16 Bits, Bit 15-0
#define BTN_bOutShort_T1_Dpt2_Press             17      // 16 Bits, Bit 15-0
#define BTN_bOutShort_T1_Dpt2_Release           19      // 16 Bits, Bit 15-0
#define BTN_bOutShort_T2_Dpt2_Press             21      // 16 Bits, Bit 15-0
#define BTN_bOutShort_T2_Dpt2_Release           23      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T1_Dpt2_Press              25      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T1_Dpt2_Release            27      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T2_Dpt2_Press              29      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T2_Dpt2_Release            31      // 16 Bits, Bit 15-0
#define BTN_bOutExtraLong_T1_Dpt2_Press         33      // 16 Bits, Bit 15-0
#define BTN_bOutExtraLong_T1_Dpt2_Release       35      // 16 Bits, Bit 15-0
#define BTN_bOutExtraLong_T2_Dpt2_Press         37      // 16 Bits, Bit 15-0
#define BTN_bOutExtraLong_T2_Dpt2_Release       39      // 16 Bits, Bit 15-0
#define BTN_bOutMulti_Click1_Dpt2               41      // 16 Bits, Bit 15-0
#define BTN_bOutMulti_Click2_Dpt2               43      // 16 Bits, Bit 15-0
#define BTN_bOutMulti_Click3_Dpt2               45      // 16 Bits, Bit 15-0
#define BTN_bOutShort_T1_Dpt5_Press             17      // uint16_t
#define BTN_bOutShort_T1_Dpt5_Release           19      // uint16_t
#define BTN_bOutShort_T2_Dpt5_Press             21      // uint16_t
#define BTN_bOutShort_T2_Dpt5_Release           23      // uint16_t
#define BTN_bOutLong_T1_Dpt5_Press              25      // uint16_t
#define BTN_bOutLong_T1_Dpt5_Release            27      // uint16_t
#define BTN_bOutLong_T2_Dpt5_Press              29      // uint16_t
#define BTN_bOutLong_T2_Dpt5_Release            31      // uint16_t
#define BTN_bOutExtraLong_T1_Dpt5_Press         33      // uint16_t
#define BTN_bOutExtraLong_T1_Dpt5_Release       35      // uint16_t
#define BTN_bOutExtraLong_T2_Dpt5_Press         37      // uint16_t
#define BTN_bOutExtraLong_T2_Dpt5_Release       39      // uint16_t
#define BTN_bOutMulti_Click1_Dpt5               41      // uint16_t
#define BTN_bOutMulti_Click2_Dpt5               43      // uint16_t
#define BTN_bOutMulti_Click3_Dpt5               45      // uint16_t
#define BTN_bOutShort_T1_Dpt5001_Press          17      // uint16_t
#define BTN_bOutShort_T1_Dpt5001_Release        19      // uint16_t
#define BTN_bOutShort_T2_Dpt5001_Press          21      // uint16_t
#define BTN_bOutShort_T2_Dpt5001_Release        23      // uint16_t
#define BTN_bOutLong_T1_Dpt5001_Press           25      // uint16_t
#define BTN_bOutLong_T1_Dpt5001_Release         27      // uint16_t
#define BTN_bOutLong_T2_Dpt5001_Press           29      // uint16_t
#define BTN_bOutLong_T2_Dpt5001_Release         31      // uint16_t
#define BTN_bOutExtraLong_T1_Dpt5001_Press      33      // uint16_t
#define BTN_bOutExtraLong_T1_Dpt5001_Release    35      // uint16_t
#define BTN_bOutExtraLong_T2_Dpt5001_Press      37      // uint16_t
#define BTN_bOutExtraLong_T2_Dpt5001_Release    39      // uint16_t
#define BTN_bOutMulti_Click1_Dpt5001            41      // uint16_t
#define BTN_bOutMulti_Click2_Dpt5001            43      // uint16_t
#define BTN_bOutMulti_Click3_Dpt5001            45      // uint16_t
#define BTN_bOutShort_T1_Dpt7_Press             17      // uint16_t
#define BTN_bOutShort_T1_Dpt7_Release           19      // uint16_t
#define BTN_bOutShort_T2_Dpt7_Press             21      // uint16_t
#define BTN_bOutShort_T2_Dpt7_Release           23      // uint16_t
#define BTN_bOutLong_T1_Dpt7_Press              25      // uint16_t
#define BTN_bOutLong_T1_Dpt7_Release            27      // uint16_t
#define BTN_bOutLong_T2_Dpt7_Press              29      // uint16_t
#define BTN_bOutLong_T2_Dpt7_Release            31      // uint16_t
#define BTN_bOutExtraLong_T1_Dpt7_Press         33      // uint16_t
#define BTN_bOutExtraLong_T1_Dpt7_Release       35      // uint16_t
#define BTN_bOutExtraLong_T2_Dpt7_Press         37      // uint16_t
#define BTN_bOutExtraLong_T2_Dpt7_Release       39      // uint16_t
#define BTN_bOutMulti_Click1_Dpt7               41      // uint16_t
#define BTN_bOutMulti_Click2_Dpt7               43      // uint16_t
#define BTN_bOutMulti_Click3_Dpt7               45      // uint16_t
#define BTN_bOutShort_T1_Dpt18_Press            17      // 16 Bits, Bit 15-0
#define BTN_bOutShort_T1_Dpt18_Release          19      // 16 Bits, Bit 15-0
#define BTN_bOutShort_T2_Dpt18_Press            21      // 16 Bits, Bit 15-0
#define BTN_bOutShort_T2_Dpt18_Release          23      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T1_Dpt18_Press             25      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T1_Dpt18_Release           27      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T2_Dpt18_Press             29      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T2_Dpt18_Release           31      // 16 Bits, Bit 15-0
#define BTN_bOutExtraLong_T1_Dpt18_Press        33      // 16 Bits, Bit 15-0
#define BTN_bOutExtraLong_T1_Dpt18_Release      35      // 16 Bits, Bit 15-0
#define BTN_bOutExtraLong_T2_Dpt18_Press        37      // 16 Bits, Bit 15-0
#define BTN_bOutExtraLong_T2_Dpt18_Release      39      // 16 Bits, Bit 15-0
#define BTN_bOutMulti_Click1_Dpt18              41      // 16 Bits, Bit 15-0
#define BTN_bOutMulti_Click2_Dpt18              43      // 16 Bits, Bit 15-0
#define BTN_bOutMulti_Click3_Dpt18              45      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T1_Dpt3007_Press           25      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T1_Dpt3007_PressSingle     25      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T1_Dpt3007_Release         27      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T2_Dpt3007_Press           29      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T2_Dpt3007_Release         31      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T1_Dpt3008_Press           25      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T1_Dpt3008_PressSingle     25      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T1_Dpt3008_Release         27      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T2_Dpt3008_Press           29      // 16 Bits, Bit 15-0
#define BTN_bOutLong_T2_Dpt3008_Release         31      // 16 Bits, Bit 15-0
#define BTN_bOut2Short_T1                       47      // 2 Bits, Bit 7-6
#define     BTN_bOut2Short_T1Mask 0xC0
#define     BTN_bOut2Short_T1Shift 6
#define BTN_bOut2Short_T2                       47      // 2 Bits, Bit 5-4
#define     BTN_bOut2Short_T2Mask 0x30
#define     BTN_bOut2Short_T2Shift 4
#define BTN_bOut2Long_T1                        47      // 2 Bits, Bit 3-2
#define     BTN_bOut2Long_T1Mask 0x0C
#define     BTN_bOut2Long_T1Shift 2
#define BTN_bOut2Long_T2                        47      // 2 Bits, Bit 1-0
#define     BTN_bOut2Long_T2Mask 0x03
#define     BTN_bOut2Long_T2Shift 0
#define BTN_bOut2ExtraLong_T1                   48      // 2 Bits, Bit 7-6
#define     BTN_bOut2ExtraLong_T1Mask 0xC0
#define     BTN_bOut2ExtraLong_T1Shift 6
#define BTN_bOut2ExtraLong_T2                   48      // 2 Bits, Bit 5-4
#define     BTN_bOut2ExtraLong_T2Mask 0x30
#define     BTN_bOut2ExtraLong_T2Shift 4
#define BTN_bStatusFallbackTime                 49      // uint16_t
#define BTN_bStatusThresholdHigh                51      // uint8_t
#define BTN_bStatusThresholdLow                 52      // uint8_t

// Modus
#define ParamBTN_bMode                               ((knx.paramByte(BTN_ParamCalcIndex(BTN_bMode)) & BTN_bModeMask) >> BTN_bModeShift)
// Sperre
#define ParamBTN_bLock                               ((knx.paramByte(BTN_ParamCalcIndex(BTN_bLock)) & BTN_bLockMask) >> BTN_bLockShift)
// Ausgabe der Klickanzahl
#define ParamBTN_bMultiClickCount                    ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bMultiClickCount)) & BTN_bMultiClickCountMask))
// Dynamische Richtung
#define ParamBTN_bDynamicStatus                      ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bDynamicStatus)) & BTN_bDynamicStatusMask))
//    1. Taster
#define ParamBTN_bInA                                (knx.paramByte(BTN_ParamCalcIndex(BTN_bInA)))
//    2. Taster
#define ParamBTN_bInB                                (knx.paramByte(BTN_ParamCalcIndex(BTN_bInB)))
// Mehrfach-Klick
#define ParamBTN_bReactionTimeMultiClick             (knx.paramByte(BTN_ParamCalcIndex(BTN_bReactionTimeMultiClick)))
// Langer Tastendruck
#define ParamBTN_bReactionTimeLong                   (knx.paramByte(BTN_ParamCalcIndex(BTN_bReactionTimeLong)))
// Extra langer Tastendruck
#define ParamBTN_bReactionTimeExtraLong              (knx.paramByte(BTN_ParamCalcIndex(BTN_bReactionTimeExtraLong)))
// Datentyp
#define ParamBTN_bOutShort_DPT                       (knx.paramByte(BTN_ParamCalcIndex(BTN_bOutShort_DPT)))
// Datentyp
#define ParamBTN_bOutLong_DPT                        (knx.paramByte(BTN_ParamCalcIndex(BTN_bOutLong_DPT)))
// Datentyp
#define ParamBTN_bOutExtraLong_DPT                   (knx.paramByte(BTN_ParamCalcIndex(BTN_bOutExtraLong_DPT)))
// Datentyp
#define ParamBTN_bOutMulti_DPT                       (knx.paramByte(BTN_ParamCalcIndex(BTN_bOutMulti_DPT)))
// 1. Klick
#define ParamBTN_bOutMulti_Click1_Active             ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bOutMulti_Click1_Active)) & BTN_bOutMulti_Click1_ActiveMask))
// 2. Klick
#define ParamBTN_bOutMulti_Click2_Active             ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bOutMulti_Click2_Active)) & BTN_bOutMulti_Click2_ActiveMask))
// 3. Klick
#define ParamBTN_bOutMulti_Click3_Active             ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bOutMulti_Click3_Active)) & BTN_bOutMulti_Click3_ActiveMask))
// Wert beim Drücken
#define ParamBTN_bOutShort_T1_Active_Press           ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bOutShort_T1_Active_Press)) & BTN_bOutShort_T1_Active_PressMask))
// Wert beim Loslassen
#define ParamBTN_bOutShort_T1_Active_Release         ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bOutShort_T1_Active_Release)) & BTN_bOutShort_T1_Active_ReleaseMask))
// Wert beim Drücken
#define ParamBTN_bOutShort_T2_Active_Press           ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bOutShort_T2_Active_Press)) & BTN_bOutShort_T2_Active_PressMask))
// Wert beim Loslassen
#define ParamBTN_bOutShort_T2_Active_Release         ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bOutShort_T2_Active_Release)) & BTN_bOutShort_T2_Active_ReleaseMask))
// Wert beim Drücken
#define ParamBTN_bOutLong_T1_Active_Press            ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bOutLong_T1_Active_Press)) & BTN_bOutLong_T1_Active_PressMask))
// Wert beim Loslassen
#define ParamBTN_bOutLong_T1_Active_Release          ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bOutLong_T1_Active_Release)) & BTN_bOutLong_T1_Active_ReleaseMask))
// Wert beim Drücken
#define ParamBTN_bOutLong_T2_Active_Press            ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bOutLong_T2_Active_Press)) & BTN_bOutLong_T2_Active_PressMask))
// Wert beim Loslassen
#define ParamBTN_bOutLong_T2_Active_Release          ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bOutLong_T2_Active_Release)) & BTN_bOutLong_T2_Active_ReleaseMask))
// Wert beim Drücken
#define ParamBTN_bOutExtraLong_T1_Active_Press       ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bOutExtraLong_T1_Active_Press)) & BTN_bOutExtraLong_T1_Active_PressMask))
// Wert beim Loslassen
#define ParamBTN_bOutExtraLong_T1_Active_Release     ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bOutExtraLong_T1_Active_Release)) & BTN_bOutExtraLong_T1_Active_ReleaseMask))
// Wert beim Drücken
#define ParamBTN_bOutExtraLong_T2_Active_Press       ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bOutExtraLong_T2_Active_Press)) & BTN_bOutExtraLong_T2_Active_PressMask))
// Wert beim Loslassen
#define ParamBTN_bOutExtraLong_T2_Active_Release     ((bool)(knx.paramByte(BTN_ParamCalcIndex(BTN_bOutExtraLong_T2_Active_Release)) & BTN_bOutExtraLong_T2_Active_ReleaseMask))
// 
#define ParamBTN_bOutShort_T1_Dpt1_Press             (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T1_Dpt1_Press)))
// 
#define ParamBTN_bOutShort_T1_Dpt1_Release           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T1_Dpt1_Release)))
// 
#define ParamBTN_bOutShort_T2_Dpt1_Press             (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T2_Dpt1_Press)))
// 
#define ParamBTN_bOutShort_T2_Dpt1_Release           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T2_Dpt1_Release)))
// 
#define ParamBTN_bOutLong_T1_Dpt1_Press              (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt1_Press)))
// 
#define ParamBTN_bOutLong_T1_Dpt1_Release            (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt1_Release)))
// 
#define ParamBTN_bOutLong_T2_Dpt1_Press              (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt1_Press)))
// 
#define ParamBTN_bOutLong_T2_Dpt1_Release            (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt1_Release)))
// 
#define ParamBTN_bOutExtraLong_T1_Dpt1_Press         (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T1_Dpt1_Press)))
// 
#define ParamBTN_bOutExtraLong_T1_Dpt1_Release       (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T1_Dpt1_Release)))
// 
#define ParamBTN_bOutExtraLong_T2_Dpt1_Press         (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T2_Dpt1_Press)))
// 
#define ParamBTN_bOutExtraLong_T2_Dpt1_Release       (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T2_Dpt1_Release)))
// 
#define ParamBTN_bOutMulti_Click1_Dpt1               (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click1_Dpt1)))
// 
#define ParamBTN_bOutMulti_Click2_Dpt1               (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click2_Dpt1)))
// 
#define ParamBTN_bOutMulti_Click3_Dpt1               (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click3_Dpt1)))
// 
#define ParamBTN_bOutShort_T1_Dpt2_Press             (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T1_Dpt2_Press)))
// 
#define ParamBTN_bOutShort_T1_Dpt2_Release           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T1_Dpt2_Release)))
// 
#define ParamBTN_bOutShort_T2_Dpt2_Press             (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T2_Dpt2_Press)))
// 
#define ParamBTN_bOutShort_T2_Dpt2_Release           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T2_Dpt2_Release)))
// 
#define ParamBTN_bOutLong_T1_Dpt2_Press              (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt2_Press)))
// 
#define ParamBTN_bOutLong_T1_Dpt2_Release            (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt2_Release)))
// 
#define ParamBTN_bOutLong_T2_Dpt2_Press              (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt2_Press)))
// 
#define ParamBTN_bOutLong_T2_Dpt2_Release            (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt2_Release)))
// 
#define ParamBTN_bOutExtraLong_T1_Dpt2_Press         (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T1_Dpt2_Press)))
// 
#define ParamBTN_bOutExtraLong_T1_Dpt2_Release       (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T1_Dpt2_Release)))
// 
#define ParamBTN_bOutExtraLong_T2_Dpt2_Press         (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T2_Dpt2_Press)))
// 
#define ParamBTN_bOutExtraLong_T2_Dpt2_Release       (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T2_Dpt2_Release)))
// 
#define ParamBTN_bOutMulti_Click1_Dpt2               (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click1_Dpt2)))
// 
#define ParamBTN_bOutMulti_Click2_Dpt2               (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click2_Dpt2)))
// 
#define ParamBTN_bOutMulti_Click3_Dpt2               (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click3_Dpt2)))
// 
#define ParamBTN_bOutShort_T1_Dpt5_Press             (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T1_Dpt5_Press)))
// 
#define ParamBTN_bOutShort_T1_Dpt5_Release           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T1_Dpt5_Release)))
// 
#define ParamBTN_bOutShort_T2_Dpt5_Press             (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T2_Dpt5_Press)))
// 
#define ParamBTN_bOutShort_T2_Dpt5_Release           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T2_Dpt5_Release)))
// 
#define ParamBTN_bOutLong_T1_Dpt5_Press              (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt5_Press)))
// 
#define ParamBTN_bOutLong_T1_Dpt5_Release            (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt5_Release)))
// 
#define ParamBTN_bOutLong_T2_Dpt5_Press              (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt5_Press)))
// 
#define ParamBTN_bOutLong_T2_Dpt5_Release            (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt5_Release)))
// 
#define ParamBTN_bOutExtraLong_T1_Dpt5_Press         (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T1_Dpt5_Press)))
// 
#define ParamBTN_bOutExtraLong_T1_Dpt5_Release       (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T1_Dpt5_Release)))
// 
#define ParamBTN_bOutExtraLong_T2_Dpt5_Press         (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T2_Dpt5_Press)))
// 
#define ParamBTN_bOutExtraLong_T2_Dpt5_Release       (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T2_Dpt5_Release)))
// 
#define ParamBTN_bOutMulti_Click1_Dpt5               (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click1_Dpt5)))
// 
#define ParamBTN_bOutMulti_Click2_Dpt5               (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click2_Dpt5)))
// 
#define ParamBTN_bOutMulti_Click3_Dpt5               (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click3_Dpt5)))
// 
#define ParamBTN_bOutShort_T1_Dpt5001_Press          (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T1_Dpt5001_Press)))
// 
#define ParamBTN_bOutShort_T1_Dpt5001_Release        (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T1_Dpt5001_Release)))
// 
#define ParamBTN_bOutShort_T2_Dpt5001_Press          (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T2_Dpt5001_Press)))
// 
#define ParamBTN_bOutShort_T2_Dpt5001_Release        (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T2_Dpt5001_Release)))
// 
#define ParamBTN_bOutLong_T1_Dpt5001_Press           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt5001_Press)))
// 
#define ParamBTN_bOutLong_T1_Dpt5001_Release         (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt5001_Release)))
// 
#define ParamBTN_bOutLong_T2_Dpt5001_Press           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt5001_Press)))
// 
#define ParamBTN_bOutLong_T2_Dpt5001_Release         (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt5001_Release)))
// 
#define ParamBTN_bOutExtraLong_T1_Dpt5001_Press      (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T1_Dpt5001_Press)))
// 
#define ParamBTN_bOutExtraLong_T1_Dpt5001_Release    (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T1_Dpt5001_Release)))
// 
#define ParamBTN_bOutExtraLong_T2_Dpt5001_Press      (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T2_Dpt5001_Press)))
// 
#define ParamBTN_bOutExtraLong_T2_Dpt5001_Release    (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T2_Dpt5001_Release)))
// 
#define ParamBTN_bOutMulti_Click1_Dpt5001            (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click1_Dpt5001)))
// 
#define ParamBTN_bOutMulti_Click2_Dpt5001            (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click2_Dpt5001)))
// 
#define ParamBTN_bOutMulti_Click3_Dpt5001            (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click3_Dpt5001)))
// 
#define ParamBTN_bOutShort_T1_Dpt7_Press             (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T1_Dpt7_Press)))
// 
#define ParamBTN_bOutShort_T1_Dpt7_Release           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T1_Dpt7_Release)))
// 
#define ParamBTN_bOutShort_T2_Dpt7_Press             (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T2_Dpt7_Press)))
// 
#define ParamBTN_bOutShort_T2_Dpt7_Release           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T2_Dpt7_Release)))
// 
#define ParamBTN_bOutLong_T1_Dpt7_Press              (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt7_Press)))
// 
#define ParamBTN_bOutLong_T1_Dpt7_Release            (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt7_Release)))
// 
#define ParamBTN_bOutLong_T2_Dpt7_Press              (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt7_Press)))
// 
#define ParamBTN_bOutLong_T2_Dpt7_Release            (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt7_Release)))
// 
#define ParamBTN_bOutExtraLong_T1_Dpt7_Press         (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T1_Dpt7_Press)))
// 
#define ParamBTN_bOutExtraLong_T1_Dpt7_Release       (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T1_Dpt7_Release)))
// 
#define ParamBTN_bOutExtraLong_T2_Dpt7_Press         (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T2_Dpt7_Press)))
// 
#define ParamBTN_bOutExtraLong_T2_Dpt7_Release       (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T2_Dpt7_Release)))
// 
#define ParamBTN_bOutMulti_Click1_Dpt7               (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click1_Dpt7)))
// 
#define ParamBTN_bOutMulti_Click2_Dpt7               (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click2_Dpt7)))
// 
#define ParamBTN_bOutMulti_Click3_Dpt7               (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click3_Dpt7)))
// 
#define ParamBTN_bOutShort_T1_Dpt18_Press            (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T1_Dpt18_Press)))
// 
#define ParamBTN_bOutShort_T1_Dpt18_Release          (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T1_Dpt18_Release)))
// 
#define ParamBTN_bOutShort_T2_Dpt18_Press            (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T2_Dpt18_Press)))
// 
#define ParamBTN_bOutShort_T2_Dpt18_Release          (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutShort_T2_Dpt18_Release)))
// 
#define ParamBTN_bOutLong_T1_Dpt18_Press             (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt18_Press)))
// 
#define ParamBTN_bOutLong_T1_Dpt18_Release           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt18_Release)))
// 
#define ParamBTN_bOutLong_T2_Dpt18_Press             (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt18_Press)))
// 
#define ParamBTN_bOutLong_T2_Dpt18_Release           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt18_Release)))
// 
#define ParamBTN_bOutExtraLong_T1_Dpt18_Press        (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T1_Dpt18_Press)))
// 
#define ParamBTN_bOutExtraLong_T1_Dpt18_Release      (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T1_Dpt18_Release)))
// 
#define ParamBTN_bOutExtraLong_T2_Dpt18_Press        (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T2_Dpt18_Press)))
// 
#define ParamBTN_bOutExtraLong_T2_Dpt18_Release      (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutExtraLong_T2_Dpt18_Release)))
// 
#define ParamBTN_bOutMulti_Click1_Dpt18              (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click1_Dpt18)))
// 
#define ParamBTN_bOutMulti_Click2_Dpt18              (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click2_Dpt18)))
// 
#define ParamBTN_bOutMulti_Click3_Dpt18              (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutMulti_Click3_Dpt18)))
// Wert beim Drücken
#define ParamBTN_bOutLong_T1_Dpt3007_Press           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt3007_Press)))
// Wert beim Drücken
#define ParamBTN_bOutLong_T1_Dpt3007_PressSingle     (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt3007_PressSingle)))
// 
#define ParamBTN_bOutLong_T1_Dpt3007_Release         (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt3007_Release)))
// Wert beim Drücken
#define ParamBTN_bOutLong_T2_Dpt3007_Press           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt3007_Press)))
// 
#define ParamBTN_bOutLong_T2_Dpt3007_Release         (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt3007_Release)))
// Wert beim Drücken
#define ParamBTN_bOutLong_T1_Dpt3008_Press           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt3008_Press)))
// Wert beim Drücken
#define ParamBTN_bOutLong_T1_Dpt3008_PressSingle     (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt3008_PressSingle)))
// 
#define ParamBTN_bOutLong_T1_Dpt3008_Release         (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T1_Dpt3008_Release)))
// Wert beim Drücken
#define ParamBTN_bOutLong_T2_Dpt3008_Press           (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt3008_Press)))
// 
#define ParamBTN_bOutLong_T2_Dpt3008_Release         (knx.paramWord(BTN_ParamCalcIndex(BTN_bOutLong_T2_Dpt3008_Release)))
// Zusatzausgang (DPT1 beim Loslassen)
#define ParamBTN_bOut2Short_T1                       ((knx.paramByte(BTN_ParamCalcIndex(BTN_bOut2Short_T1)) & BTN_bOut2Short_T1Mask) >> BTN_bOut2Short_T1Shift)
// Zusatzausgang (DPT1 beim Loslassen)
#define ParamBTN_bOut2Short_T2                       ((knx.paramByte(BTN_ParamCalcIndex(BTN_bOut2Short_T2)) & BTN_bOut2Short_T2Mask) >> BTN_bOut2Short_T2Shift)
// Zusatzausgang (DPT1 beim Loslassen)
#define ParamBTN_bOut2Long_T1                        ((knx.paramByte(BTN_ParamCalcIndex(BTN_bOut2Long_T1)) & BTN_bOut2Long_T1Mask) >> BTN_bOut2Long_T1Shift)
// Zusatzausgang (DPT1 beim Loslassen)
#define ParamBTN_bOut2Long_T2                        (knx.paramByte(BTN_ParamCalcIndex(BTN_bOut2Long_T2)) & BTN_bOut2Long_T2Mask)
// Zusatzausgang (DPT1 beim Loslassen)
#define ParamBTN_bOut2ExtraLong_T1                   ((knx.paramByte(BTN_ParamCalcIndex(BTN_bOut2ExtraLong_T1)) & BTN_bOut2ExtraLong_T1Mask) >> BTN_bOut2ExtraLong_T1Shift)
// Zusatzausgang (DPT1 beim Loslassen)
#define ParamBTN_bOut2ExtraLong_T2                   ((knx.paramByte(BTN_ParamCalcIndex(BTN_bOut2ExtraLong_T2)) & BTN_bOut2ExtraLong_T2Mask) >> BTN_bOut2ExtraLong_T2Shift)
// Verzögerung
#define ParamBTN_bStatusFallbackTime                 (knx.paramWord(BTN_ParamCalcIndex(BTN_bStatusFallbackTime)))
// Oberer Schwellwert
#define ParamBTN_bStatusThresholdHigh                (knx.paramByte(BTN_ParamCalcIndex(BTN_bStatusThresholdHigh)))
// Unterer Schwellwert
#define ParamBTN_bStatusThresholdLow                 (knx.paramByte(BTN_ParamCalcIndex(BTN_bStatusThresholdLow)))

// deprecated
#define BTN_KoOffset 400

// Communication objects per channel (multiple occurrence)
#define BTN_KoBlockOffset 400
#define BTN_KoBlockSize 12

#define BTN_KoCalcNumber(index) (index + BTN_KoBlockOffset + _channelIndex * BTN_KoBlockSize)
#define BTN_KoCalcIndex(number) ((number >= BTN_KoCalcNumber(0) && number < BTN_KoCalcNumber(BTN_KoBlockSize)) ? (number - BTN_KoBlockOffset) % BTN_KoBlockSize : -1)
#define BTN_KoCalcChannel(number) ((number >= BTN_KoBlockOffset && number < BTN_KoBlockOffset + BTN_ChannelCount * BTN_KoBlockSize) ? (number - BTN_KoBlockOffset) / BTN_KoBlockSize : -1)

#define BTN_KoLock 0
#define BTN_KoIn1 1
#define BTN_KoIn2 2
#define BTN_KoOut1Status 3
#define BTN_KoOut2Status 4
#define BTN_KoOut3Status 5
#define BTN_KoOut1 6
#define BTN_KoOut2 7
#define BTN_KoOut3 8
#define BTN_KoOut4 9
#define BTN_KoOut5 10
#define BTN_KoOut6 11

// 
#define KoBTN_Lock                                (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoLock)))
// 
#define KoBTN_In1                                 (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoIn1)))
// 
#define KoBTN_In2                                 (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoIn2)))
// 
#define KoBTN_Out1Status                          (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoOut1Status)))
// 
#define KoBTN_Out2Status                          (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoOut2Status)))
// 
#define KoBTN_Out3Status                          (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoOut3Status)))
// 
#define KoBTN_Out1                                (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoOut1)))
// 
#define KoBTN_Out2                                (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoOut2)))
// 
#define KoBTN_Out3                                (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoOut3)))
// 
#define KoBTN_Out4                                (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoOut4)))
// 
#define KoBTN_Out5                                (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoOut5)))
// 
#define KoBTN_Out6                                (knx.getGroupObject(BTN_KoCalcNumber(BTN_KoOut6)))



// Header generation for Module 'BASE_KommentarModule'

#define BASE_KommentarModuleCount 0
#define BASE_KommentarModuleModuleParamSize 0
#define BASE_KommentarModuleSubmodulesParamSize 0
#define BASE_KommentarModuleParamSize 0
#define BASE_KommentarModuleParamOffset 14329
#define BASE_KommentarModuleCalcIndex(index, m1) (index + BASE_KommentarModuleParamOffset + _channelIndex * BASE_KommentarModuleCount * BASE_KommentarModuleParamSize + m1 * BASE_KommentarModuleParamSize)



