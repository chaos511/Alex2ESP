#ifndef ALEXA_INTERFACE_H
#define ALEXA_INTERFACE_H

#include <string>
#include <unordered_map>
#include <Arduino.h>

// Enum for Alexa Interface Types
enum class AlexaInterfaceType
{
    APPLICATION_STATE_REPORTER,
    AUDIO_PLAY_QUEUE,
    AUTHORIZATION_CONTROLLER,
    AUTOMATION_MANAGEMENT,
    AUTOMOTIVE_VEHICLE_DATA,
    BRIGHTNESS_CONTROLLER,
    CAMERA_LIVE_VIEW_CONTROLLER,
    CAMERA_STREAM_CONTROLLER,
    CHANNEL_CONTROLLER,
    COLOR_CONTROLLER,
    COLOR_TEMPERATURE_CONTROLLER,
    COMMISSIONABLE,
    CONSENT_MANAGEMENT_CONSENT_REQUIRED_REPORTER,
    CONTACT_SENSOR,
    COOKING,
    COOKING_FOOD_TEMPERATURE_CONTROLLER,
    COOKING_FOOD_TEMPERATURE_SENSOR,
    COOKING_PRESET_CONTROLLER,
    COOKING_TEMPERATURE_CONTROLLER,
    COOKING_TEMPERATURE_SENSOR,
    COOKING_TIME_CONTROLLER,
    DATA_CONTROLLER,
    DEVICE_USAGE_ESTIMATION,
    DEVICE_USAGE_METER,
    DOORBELL_EVENT_SOURCE,
    ENDPOINT_HEALTH,
    EQUALIZER_CONTROLLER,
    INPUT_CONTROLLER,
    INVENTORY_LEVEL_SENSOR,
    INVENTORY_LEVEL_USAGE_SENSOR,
    INVENTORY_USAGE_SENSOR,
    KEYPAD_CONTROLLER,
    LAUNCHER,
    LOCK_CONTROLLER,
    MEDIA_PLAYBACK,
    MEDIA_PLAY_QUEUE,
    MEDIA_SEARCH,
    MODE_CONTROLLER,
    MOTION_SENSOR,
    PERCENTAGE_CONTROLLER,
    PLAYBACK_CONTROLLER,
    PLAYBACK_STATE_REPORTER,
    POWER_CONTROLLER,
    POWER_LEVEL_CONTROLLER,
    PROACTIVE_NOTIFICATION_SOURCE,
    RANGE_CONTROLLER,
    RECORD_CONTROLLER,
    REMOTE_VIDEO_PLAYER,
    RTC_SESSION_CONTROLLER,
    SCENE_CONTROLLER,
    SECURITY_PANEL_CONTROLLER,
    SECURITY_PANEL_CONTROLLER_ALERT,
    SEEK_CONTROLLER,
    SIMPLE_EVENT_SOURCE,
    SMART_VISION_OBJECT_DETECTION_SENSOR,
    SMART_VISION_SNAPSHOT_PROVIDER,
    SPEAKER,
    STEP_SPEAKER,
    TEMPERATURE_SENSOR,
    THERMOSTAT_CONTROLLER,
    THERMOSTAT_CONTROLLER_CONFIGURATION,
    THERMOSTAT_CONTROLLER_HVAC_COMPONENTS,
    THERMOSTAT_CONTROLLER_SCHEDULE,
    TIME_HOLD_CONTROLLER,
    TOGGLE_CONTROLLER,
    UI_CONTROLLER,
    USER_PREFERENCE,
    VIDEO_RECORDER,
    WAKE_ON_LAN_CONTROLLER,
    UNKNOWN
};

// Utility class to handle Alexa Interface type details
class AlexaInterfaceUtils
{
public:

    static AlexaInterfaceType fromString(const String& str)
    {
        if (str == "Alexa.ApplicationStateReporter")
            return AlexaInterfaceType::APPLICATION_STATE_REPORTER;
        if (str == "Alexa.Audio.PlayQueue")
            return AlexaInterfaceType::AUDIO_PLAY_QUEUE;
        if (str == "Alexa.AuthorizationController")
            return AlexaInterfaceType::AUTHORIZATION_CONTROLLER;
        if (str == "Alexa.AutomationManagement")
            return AlexaInterfaceType::AUTOMATION_MANAGEMENT;
        if (str == "Alexa.Automotive.VehicleData")
            return AlexaInterfaceType::AUTOMOTIVE_VEHICLE_DATA;
        if (str == "Alexa.BrightnessController")
            return AlexaInterfaceType::BRIGHTNESS_CONTROLLER;
        if (str == "Alexa.Camera.LiveViewController")
            return AlexaInterfaceType::CAMERA_LIVE_VIEW_CONTROLLER;
        if (str == "Alexa.CameraStreamController")
            return AlexaInterfaceType::CAMERA_STREAM_CONTROLLER;
        if (str == "Alexa.ChannelController")
            return AlexaInterfaceType::CHANNEL_CONTROLLER;
        if (str == "Alexa.ColorController")
            return AlexaInterfaceType::COLOR_CONTROLLER;
        if (str == "Alexa.ColorTemperatureController")
            return AlexaInterfaceType::COLOR_TEMPERATURE_CONTROLLER;
        if (str == "Alexa.Commissionable")
            return AlexaInterfaceType::COMMISSIONABLE;
        if (str == "Alexa.ConsentManagement.ConsentRequiredReporter")
            return AlexaInterfaceType::CONSENT_MANAGEMENT_CONSENT_REQUIRED_REPORTER;
        if (str == "Alexa.ContactSensor")
            return AlexaInterfaceType::CONTACT_SENSOR;
        if (str == "Alexa.Cooking")
            return AlexaInterfaceType::COOKING;
        if (str == "Alexa.Cooking.FoodTemperatureController")
            return AlexaInterfaceType::COOKING_FOOD_TEMPERATURE_CONTROLLER;
        if (str == "Alexa.Cooking.FoodTemperatureSensor")
            return AlexaInterfaceType::COOKING_FOOD_TEMPERATURE_SENSOR;
        if (str == "Alexa.Cooking.PresetController")
            return AlexaInterfaceType::COOKING_PRESET_CONTROLLER;
        if (str == "Alexa.Cooking.TemperatureController")
            return AlexaInterfaceType::COOKING_TEMPERATURE_CONTROLLER;
        if (str == "Alexa.Cooking.TemperatureSensor")
            return AlexaInterfaceType::COOKING_TEMPERATURE_SENSOR;
        if (str == "Alexa.Cooking.TimeController")
            return AlexaInterfaceType::COOKING_TIME_CONTROLLER;
        if (str == "Alexa.DataController")
            return AlexaInterfaceType::DATA_CONTROLLER;
        if (str == "Alexa.DeviceUsage.Estimation")
            return AlexaInterfaceType::DEVICE_USAGE_ESTIMATION;
        if (str == "Alexa.DeviceUsage.Meter")
            return AlexaInterfaceType::DEVICE_USAGE_METER;
        if (str == "Alexa.DoorbellEventSource")
            return AlexaInterfaceType::DOORBELL_EVENT_SOURCE;
        if (str == "Alexa.EndpointHealth")
            return AlexaInterfaceType::ENDPOINT_HEALTH;
        if (str == "Alexa.EqualizerController")
            return AlexaInterfaceType::EQUALIZER_CONTROLLER;
        if (str == "Alexa.InputController")
            return AlexaInterfaceType::INPUT_CONTROLLER;
        if (str == "Alexa.InventoryLevelSensor")
            return AlexaInterfaceType::INVENTORY_LEVEL_SENSOR;
        if (str == "Alexa.InventoryLevelUsageSensor")
            return AlexaInterfaceType::INVENTORY_LEVEL_USAGE_SENSOR;
        if (str == "Alexa.InventoryUsageSensor")
            return AlexaInterfaceType::INVENTORY_USAGE_SENSOR;
        if (str == "Alexa.KeypadController")
            return AlexaInterfaceType::KEYPAD_CONTROLLER;
        if (str == "Alexa.Launcher")
            return AlexaInterfaceType::LAUNCHER;
        if (str == "Alexa.LockController")
            return AlexaInterfaceType::LOCK_CONTROLLER;
        if (str == "Alexa.Media.Playback")
            return AlexaInterfaceType::MEDIA_PLAYBACK;
        if (str == "Alexa.Media.PlayQueue")
            return AlexaInterfaceType::MEDIA_PLAY_QUEUE;
        if (str == "Alexa.Media.Search")
            return AlexaInterfaceType::MEDIA_SEARCH;
        if (str == "Alexa.ModeController")
            return AlexaInterfaceType::MODE_CONTROLLER;
        if (str == "Alexa.MotionSensor")
            return AlexaInterfaceType::MOTION_SENSOR;
        if (str == "Alexa.PercentageController")
            return AlexaInterfaceType::PERCENTAGE_CONTROLLER;
        if (str == "Alexa.PlaybackController")
            return AlexaInterfaceType::PLAYBACK_CONTROLLER;
        if (str == "Alexa.PlaybackStateReporter")
            return AlexaInterfaceType::PLAYBACK_STATE_REPORTER;
        if (str == "Alexa.PowerController")
            return AlexaInterfaceType::POWER_CONTROLLER;
        if (str == "Alexa.PowerLevelController")
            return AlexaInterfaceType::POWER_LEVEL_CONTROLLER;
        if (str == "Alexa.ProactiveNotificationSource")
            return AlexaInterfaceType::PROACTIVE_NOTIFICATION_SOURCE;
        if (str == "Alexa.RangeController")
            return AlexaInterfaceType::RANGE_CONTROLLER;
        if (str == "Alexa.RecordController")
            return AlexaInterfaceType::RECORD_CONTROLLER;
        if (str == "Alexa.RemoteVideoPlayer")
            return AlexaInterfaceType::REMOTE_VIDEO_PLAYER;
        if (str == "Alexa.RTCSessionController")
            return AlexaInterfaceType::RTC_SESSION_CONTROLLER;
        if (str == "Alexa.SceneController")
            return AlexaInterfaceType::SCENE_CONTROLLER;
        if (str == "Alexa.SecurityPanelController")
            return AlexaInterfaceType::SECURITY_PANEL_CONTROLLER;
        if (str == "Alexa.SecurityPanelController.Alert")
            return AlexaInterfaceType::SECURITY_PANEL_CONTROLLER_ALERT;
        if (str == "Alexa.SeekController")
            return AlexaInterfaceType::SEEK_CONTROLLER;
        if (str == "Alexa.SimpleEventSource")
            return AlexaInterfaceType::SIMPLE_EVENT_SOURCE;
        if (str == "Alexa.SmartVision.ObjectDetectionSensor")
            return AlexaInterfaceType::SMART_VISION_OBJECT_DETECTION_SENSOR;
        if (str == "Alexa.SmartVision.SnapshotProvider")
            return AlexaInterfaceType::SMART_VISION_SNAPSHOT_PROVIDER;
        if (str == "Alexa.Speaker")
            return AlexaInterfaceType::SPEAKER;
        if (str == "Alexa.StepSpeaker")
            return AlexaInterfaceType::STEP_SPEAKER;
        if (str == "Alexa.TemperatureSensor")
            return AlexaInterfaceType::TEMPERATURE_SENSOR;
        if (str == "Alexa.ThermostatController")
            return AlexaInterfaceType::THERMOSTAT_CONTROLLER;
        if (str == "Alexa.ThermostatController.Configuration")
            return AlexaInterfaceType::THERMOSTAT_CONTROLLER_CONFIGURATION;
        if (str == "Alexa.ThermostatController.HVAC.Components")
            return AlexaInterfaceType::THERMOSTAT_CONTROLLER_HVAC_COMPONENTS;
        if (str == "Alexa.ThermostatController.Schedule")
            return AlexaInterfaceType::THERMOSTAT_CONTROLLER_SCHEDULE;
        if (str == "Alexa.TimeHoldController")
            return AlexaInterfaceType::TIME_HOLD_CONTROLLER;
        if (str == "Alexa.ToggleController")
            return AlexaInterfaceType::TOGGLE_CONTROLLER;
        if (str == "Alexa.UIController")
            return AlexaInterfaceType::UI_CONTROLLER;
        if (str == "Alexa.UserPreference")
            return AlexaInterfaceType::USER_PREFERENCE;
        if (str == "Alexa.VideoRecorder")
            return AlexaInterfaceType::VIDEO_RECORDER;
        if (str == "Alexa.WakeOnLANController")
            return AlexaInterfaceType::WAKE_ON_LAN_CONTROLLER;

        return AlexaInterfaceType::UNKNOWN; 
    }


    static String toString(AlexaInterfaceType type)
    {
        switch (type)
        {
        case AlexaInterfaceType::APPLICATION_STATE_REPORTER:
            return "Alexa.ApplicationStateReporter";
        case AlexaInterfaceType::AUDIO_PLAY_QUEUE:
            return "Alexa.Audio.PlayQueue";
        case AlexaInterfaceType::AUTHORIZATION_CONTROLLER:
            return "Alexa.AuthorizationController";
        case AlexaInterfaceType::AUTOMATION_MANAGEMENT:
            return "Alexa.AutomationManagement";
        case AlexaInterfaceType::AUTOMOTIVE_VEHICLE_DATA:
            return "Alexa.Automotive.VehicleData";
        case AlexaInterfaceType::BRIGHTNESS_CONTROLLER:
            return "Alexa.BrightnessController";
        case AlexaInterfaceType::CAMERA_LIVE_VIEW_CONTROLLER:
            return "Alexa.Camera.LiveViewController";
        case AlexaInterfaceType::CAMERA_STREAM_CONTROLLER:
            return "Alexa.CameraStreamController";
        case AlexaInterfaceType::CHANNEL_CONTROLLER:
            return "Alexa.ChannelController";
        case AlexaInterfaceType::COLOR_CONTROLLER:
            return "Alexa.ColorController";
        case AlexaInterfaceType::COLOR_TEMPERATURE_CONTROLLER:
            return "Alexa.ColorTemperatureController";
        case AlexaInterfaceType::COMMISSIONABLE:
            return "Alexa.Commissionable";
        case AlexaInterfaceType::CONSENT_MANAGEMENT_CONSENT_REQUIRED_REPORTER:
            return "Alexa.ConsentManagement.ConsentRequiredReporter";
        case AlexaInterfaceType::CONTACT_SENSOR:
            return "Alexa.ContactSensor";
        case AlexaInterfaceType::COOKING:
            return "Alexa.Cooking";
        case AlexaInterfaceType::COOKING_FOOD_TEMPERATURE_CONTROLLER:
            return "Alexa.Cooking.FoodTemperatureController";
        case AlexaInterfaceType::COOKING_FOOD_TEMPERATURE_SENSOR:
            return "Alexa.Cooking.FoodTemperatureSensor";
        case AlexaInterfaceType::COOKING_PRESET_CONTROLLER:
            return "Alexa.Cooking.PresetController";
        case AlexaInterfaceType::COOKING_TEMPERATURE_CONTROLLER:
            return "Alexa.Cooking.TemperatureController";
        case AlexaInterfaceType::COOKING_TEMPERATURE_SENSOR:
            return "Alexa.Cooking.TemperatureSensor";
        case AlexaInterfaceType::COOKING_TIME_CONTROLLER:
            return "Alexa.Cooking.TimeController";
        case AlexaInterfaceType::DATA_CONTROLLER:
            return "Alexa.DataController";
        case AlexaInterfaceType::DEVICE_USAGE_ESTIMATION:
            return "Alexa.DeviceUsage.Estimation";
        case AlexaInterfaceType::DEVICE_USAGE_METER:
            return "Alexa.DeviceUsage.Meter";
        case AlexaInterfaceType::DOORBELL_EVENT_SOURCE:
            return "Alexa.DoorbellEventSource";
        case AlexaInterfaceType::ENDPOINT_HEALTH:
            return "Alexa.EndpointHealth";
        case AlexaInterfaceType::EQUALIZER_CONTROLLER:
            return "Alexa.EqualizerController";
        case AlexaInterfaceType::INPUT_CONTROLLER:
            return "Alexa.InputController";
        case AlexaInterfaceType::INVENTORY_LEVEL_SENSOR:
            return "Alexa.InventoryLevelSensor";
        case AlexaInterfaceType::INVENTORY_LEVEL_USAGE_SENSOR:
            return "Alexa.InventoryLevelUsageSensor";
        case AlexaInterfaceType::INVENTORY_USAGE_SENSOR:
            return "Alexa.InventoryUsageSensor";
        case AlexaInterfaceType::KEYPAD_CONTROLLER:
            return "Alexa.KeypadController";
        case AlexaInterfaceType::LAUNCHER:
            return "Alexa.Launcher";
        case AlexaInterfaceType::LOCK_CONTROLLER:
            return "Alexa.LockController";
        case AlexaInterfaceType::MEDIA_PLAYBACK:
            return "Alexa.Media.Playback";
        case AlexaInterfaceType::MEDIA_PLAY_QUEUE:
            return "Alexa.Media.PlayQueue";
        case AlexaInterfaceType::MEDIA_SEARCH:
            return "Alexa.Media.Search";
        case AlexaInterfaceType::MODE_CONTROLLER:
            return "Alexa.ModeController";
        case AlexaInterfaceType::MOTION_SENSOR:
            return "Alexa.MotionSensor";
        case AlexaInterfaceType::PERCENTAGE_CONTROLLER:
            return "Alexa.PercentageController";
        case AlexaInterfaceType::PLAYBACK_CONTROLLER:
            return "Alexa.PlaybackController";
        case AlexaInterfaceType::PLAYBACK_STATE_REPORTER:
            return "Alexa.PlaybackStateReporter";
        case AlexaInterfaceType::POWER_CONTROLLER:
            return "Alexa.PowerController";
        case AlexaInterfaceType::POWER_LEVEL_CONTROLLER:
            return "Alexa.PowerLevelController";
        case AlexaInterfaceType::PROACTIVE_NOTIFICATION_SOURCE:
            return "Alexa.ProactiveNotificationSource";
        case AlexaInterfaceType::RANGE_CONTROLLER:
            return "Alexa.RangeController";
        case AlexaInterfaceType::RECORD_CONTROLLER:
            return "Alexa.RecordController";
        case AlexaInterfaceType::REMOTE_VIDEO_PLAYER:
            return "Alexa.RemoteVideoPlayer";
        case AlexaInterfaceType::RTC_SESSION_CONTROLLER:
            return "Alexa.RTCSessionController";
        case AlexaInterfaceType::SCENE_CONTROLLER:
            return "Alexa.SceneController";
        case AlexaInterfaceType::SECURITY_PANEL_CONTROLLER:
            return "Alexa.SecurityPanelController";
        case AlexaInterfaceType::SECURITY_PANEL_CONTROLLER_ALERT:
            return "Alexa.SecurityPanelController.Alert";
        case AlexaInterfaceType::SEEK_CONTROLLER:
            return "Alexa.SeekController";
        case AlexaInterfaceType::SIMPLE_EVENT_SOURCE:
            return "Alexa.SimpleEventSource";
        case AlexaInterfaceType::SMART_VISION_OBJECT_DETECTION_SENSOR:
            return "Alexa.SmartVision.ObjectDetectionSensor";
        case AlexaInterfaceType::SMART_VISION_SNAPSHOT_PROVIDER:
            return "Alexa.SmartVision.SnapshotProvider";
        case AlexaInterfaceType::SPEAKER:
            return "Alexa.Speaker";
        case AlexaInterfaceType::STEP_SPEAKER:
            return "Alexa.StepSpeaker";
        case AlexaInterfaceType::TEMPERATURE_SENSOR:
            return "Alexa.TemperatureSensor";
        case AlexaInterfaceType::THERMOSTAT_CONTROLLER:
            return "Alexa.ThermostatController";
        case AlexaInterfaceType::THERMOSTAT_CONTROLLER_CONFIGURATION:
            return "Alexa.ThermostatController.Configuration";
        case AlexaInterfaceType::THERMOSTAT_CONTROLLER_HVAC_COMPONENTS:
            return "Alexa.ThermostatController.HVAC.Components";
        case AlexaInterfaceType::THERMOSTAT_CONTROLLER_SCHEDULE:
            return "Alexa.ThermostatController.Schedule";
        case AlexaInterfaceType::TIME_HOLD_CONTROLLER:
            return "Alexa.TimeHoldController";
        case AlexaInterfaceType::TOGGLE_CONTROLLER:
            return "Alexa.ToggleController";
        case AlexaInterfaceType::UI_CONTROLLER:
            return "Alexa.UIController";
        case AlexaInterfaceType::USER_PREFERENCE:
            return "Alexa.UserPreference";
        case AlexaInterfaceType::VIDEO_RECORDER:
            return "Alexa.VideoRecorder";
        case AlexaInterfaceType::WAKE_ON_LAN_CONTROLLER:
            return "Alexa.WakeOnLANController";
        default:
            return "UNKNOWN";
        }
    }

    static String getVersion(AlexaInterfaceType type)
    {
        switch (type)
        {
        case AlexaInterfaceType::APPLICATION_STATE_REPORTER:
        case AlexaInterfaceType::AUDIO_PLAY_QUEUE:
        case AlexaInterfaceType::AUTHORIZATION_CONTROLLER:
        case AlexaInterfaceType::AUTOMATION_MANAGEMENT:
        case AlexaInterfaceType::AUTOMOTIVE_VEHICLE_DATA:
        case AlexaInterfaceType::COMMISSIONABLE:
        case AlexaInterfaceType::CONSENT_MANAGEMENT_CONSENT_REQUIRED_REPORTER:
        case AlexaInterfaceType::COOKING:
        case AlexaInterfaceType::COOKING_FOOD_TEMPERATURE_CONTROLLER:
        case AlexaInterfaceType::COOKING_FOOD_TEMPERATURE_SENSOR:
        case AlexaInterfaceType::COOKING_PRESET_CONTROLLER:
        case AlexaInterfaceType::COOKING_TEMPERATURE_CONTROLLER:
        case AlexaInterfaceType::COOKING_TEMPERATURE_SENSOR:
        case AlexaInterfaceType::COOKING_TIME_CONTROLLER:
        case AlexaInterfaceType::DATA_CONTROLLER:
        case AlexaInterfaceType::DEVICE_USAGE_ESTIMATION:
        case AlexaInterfaceType::DEVICE_USAGE_METER:
        case AlexaInterfaceType::EQUALIZER_CONTROLLER:
        case AlexaInterfaceType::INVENTORY_LEVEL_SENSOR:
        case AlexaInterfaceType::INVENTORY_LEVEL_USAGE_SENSOR:
        case AlexaInterfaceType::INVENTORY_USAGE_SENSOR:
        case AlexaInterfaceType::KEYPAD_CONTROLLER:
        case AlexaInterfaceType::MEDIA_PLAYBACK:
        case AlexaInterfaceType::MEDIA_PLAY_QUEUE:
        case AlexaInterfaceType::MEDIA_SEARCH:
        case AlexaInterfaceType::PLAYBACK_STATE_REPORTER:
        case AlexaInterfaceType::PROACTIVE_NOTIFICATION_SOURCE:
        case AlexaInterfaceType::REMOTE_VIDEO_PLAYER:
        case AlexaInterfaceType::RTC_SESSION_CONTROLLER:
        case AlexaInterfaceType::SECURITY_PANEL_CONTROLLER:
        case AlexaInterfaceType::SECURITY_PANEL_CONTROLLER_ALERT:
        case AlexaInterfaceType::SIMPLE_EVENT_SOURCE:
        case AlexaInterfaceType::SMART_VISION_OBJECT_DETECTION_SENSOR:
        case AlexaInterfaceType::SMART_VISION_SNAPSHOT_PROVIDER:
        case AlexaInterfaceType::SPEAKER:
        case AlexaInterfaceType::STEP_SPEAKER:
        case AlexaInterfaceType::THERMOSTAT_CONTROLLER_CONFIGURATION:
        case AlexaInterfaceType::THERMOSTAT_CONTROLLER_HVAC_COMPONENTS:
        case AlexaInterfaceType::THERMOSTAT_CONTROLLER_SCHEDULE:
        case AlexaInterfaceType::UI_CONTROLLER:
        case AlexaInterfaceType::USER_PREFERENCE:
        case AlexaInterfaceType::VIDEO_RECORDER:
        case AlexaInterfaceType::WAKE_ON_LAN_CONTROLLER:
            return "1";

        case AlexaInterfaceType::BRIGHTNESS_CONTROLLER:
        case AlexaInterfaceType::CAMERA_STREAM_CONTROLLER:
        case AlexaInterfaceType::CHANNEL_CONTROLLER:
        case AlexaInterfaceType::COLOR_CONTROLLER:
        case AlexaInterfaceType::COLOR_TEMPERATURE_CONTROLLER:
        case AlexaInterfaceType::CONTACT_SENSOR:
        case AlexaInterfaceType::DOORBELL_EVENT_SOURCE:
        case AlexaInterfaceType::INPUT_CONTROLLER:
        case AlexaInterfaceType::LOCK_CONTROLLER:
        case AlexaInterfaceType::MODE_CONTROLLER:
        case AlexaInterfaceType::MOTION_SENSOR:
        case AlexaInterfaceType::PERCENTAGE_CONTROLLER:
        case AlexaInterfaceType::PLAYBACK_CONTROLLER:
        case AlexaInterfaceType::POWER_CONTROLLER:
        case AlexaInterfaceType::POWER_LEVEL_CONTROLLER:
        case AlexaInterfaceType::RANGE_CONTROLLER:
        case AlexaInterfaceType::RECORD_CONTROLLER:
        case AlexaInterfaceType::SCENE_CONTROLLER:
        case AlexaInterfaceType::SEEK_CONTROLLER:
        case AlexaInterfaceType::TEMPERATURE_SENSOR:
        case AlexaInterfaceType::THERMOSTAT_CONTROLLER:
        case AlexaInterfaceType::TOGGLE_CONTROLLER:
            return "3";

        case AlexaInterfaceType::LAUNCHER:
            return "1.1";
        case AlexaInterfaceType::ENDPOINT_HEALTH:
            return "3.3";
        default:
            return "UNKNOWN";
        }
    }

    static std::vector<String> getProps(AlexaInterfaceType type)
    {
        switch (type)
        {
case AlexaInterfaceType::AUTOMATION_MANAGEMENT:
    return {"automationStatuses"};
case AlexaInterfaceType::BRIGHTNESS_CONTROLLER:
    return {"brightness"};
case AlexaInterfaceType::CHANNEL_CONTROLLER:
    return {"channel"};
case AlexaInterfaceType::COLOR_CONTROLLER:
    return {"color"};
case AlexaInterfaceType::COLOR_TEMPERATURE_CONTROLLER:
    return {"colorTemperatureInKelvin"};
case AlexaInterfaceType::CONTACT_SENSOR:
    return {"detectionState"};
case AlexaInterfaceType::POWER_CONTROLLER:
    return {"powerState"};
case AlexaInterfaceType::ENDPOINT_HEALTH:
    return {"connectivity"};
case AlexaInterfaceType::TOGGLE_CONTROLLER:
    return {"toggleState"};
case AlexaInterfaceType::TEMPERATURE_SENSOR:
    return {"temperature"};

case AlexaInterfaceType::APPLICATION_STATE_REPORTER:
case AlexaInterfaceType::AUDIO_PLAY_QUEUE:
case AlexaInterfaceType::AUTHORIZATION_CONTROLLER:
case AlexaInterfaceType::AUTOMOTIVE_VEHICLE_DATA:
case AlexaInterfaceType::CAMERA_LIVE_VIEW_CONTROLLER:
case AlexaInterfaceType::CAMERA_STREAM_CONTROLLER:
case AlexaInterfaceType::COMMISSIONABLE:
case AlexaInterfaceType::CONSENT_MANAGEMENT_CONSENT_REQUIRED_REPORTER:
case AlexaInterfaceType::COOKING:
case AlexaInterfaceType::DATA_CONTROLLER:
case AlexaInterfaceType::DEVICE_USAGE_ESTIMATION:
case AlexaInterfaceType::DEVICE_USAGE_METER:
case AlexaInterfaceType::DOORBELL_EVENT_SOURCE:
case AlexaInterfaceType::EQUALIZER_CONTROLLER:
case AlexaInterfaceType::INPUT_CONTROLLER:
case AlexaInterfaceType::INVENTORY_LEVEL_SENSOR:
case AlexaInterfaceType::INVENTORY_LEVEL_USAGE_SENSOR:
case AlexaInterfaceType::INVENTORY_USAGE_SENSOR:
case AlexaInterfaceType::KEYPAD_CONTROLLER:
case AlexaInterfaceType::LAUNCHER:
case AlexaInterfaceType::LOCK_CONTROLLER:
case AlexaInterfaceType::MEDIA_PLAYBACK:
case AlexaInterfaceType::MEDIA_SEARCH:
case AlexaInterfaceType::MODE_CONTROLLER:
case AlexaInterfaceType::MOTION_SENSOR:
case AlexaInterfaceType::PERCENTAGE_CONTROLLER:
case AlexaInterfaceType::PLAYBACK_CONTROLLER:
case AlexaInterfaceType::PLAYBACK_STATE_REPORTER:
case AlexaInterfaceType::PROACTIVE_NOTIFICATION_SOURCE:
case AlexaInterfaceType::RANGE_CONTROLLER:
case AlexaInterfaceType::RECORD_CONTROLLER:
case AlexaInterfaceType::REMOTE_VIDEO_PLAYER:
case AlexaInterfaceType::RTC_SESSION_CONTROLLER:
case AlexaInterfaceType::SCENE_CONTROLLER:
case AlexaInterfaceType::SECURITY_PANEL_CONTROLLER:
case AlexaInterfaceType::SEEK_CONTROLLER:
case AlexaInterfaceType::SIMPLE_EVENT_SOURCE:
case AlexaInterfaceType::SMART_VISION_OBJECT_DETECTION_SENSOR:
case AlexaInterfaceType::SMART_VISION_SNAPSHOT_PROVIDER:
case AlexaInterfaceType::SPEAKER:
case AlexaInterfaceType::STEP_SPEAKER:
case AlexaInterfaceType::THERMOSTAT_CONTROLLER:
case AlexaInterfaceType::THERMOSTAT_CONTROLLER_CONFIGURATION:
case AlexaInterfaceType::THERMOSTAT_CONTROLLER_HVAC_COMPONENTS:
case AlexaInterfaceType::THERMOSTAT_CONTROLLER_SCHEDULE:
case AlexaInterfaceType::TIME_HOLD_CONTROLLER:
case AlexaInterfaceType::UI_CONTROLLER:
case AlexaInterfaceType::USER_PREFERENCE:
case AlexaInterfaceType::VIDEO_RECORDER:
case AlexaInterfaceType::WAKE_ON_LAN_CONTROLLER:
            return {};

        default:
            return {"UNKNOWN"};
        }
    }
};

enum class AlexaActions {
    Open,
    Close,
    Raise,
    Lower,
    SetEcoOn,
    SetEcoOff
};


class AlexaActionsUtils
{
public:
    // Helper function to convert AlexaActions enum to string
    static String toString(AlexaActions action) {
        switch (action) {
            case AlexaActions::Open: return "Alexa.Actions.Open";
            case AlexaActions::Close: return "Alexa.Actions.Close";
            case AlexaActions::Raise: return "Alexa.Actions.Raise";
            case AlexaActions::Lower: return "Alexa.Actions.Lower";
            case AlexaActions::SetEcoOn: return "Alexa.Actions.SetEcoOn";
            case AlexaActions::SetEcoOff: return "Alexa.Actions.SetEcoOff";
            default: return "Unknown";
        }
    }
};
class FriendlyName {
public:
    FriendlyName(const std::string& t, const std::string& l) 
    : text(t), locale(l) {}

    std::string text;
    std::string locale;  
};

// Updated ActionMapping class definition
class ActionMapping {
public:
    String type = "ActionsToDirective";  // Type of action mapping (always "ActionsToDirective")
    std::vector<AlexaActions> actions;   // Array of AlexaActions
    struct Directive {
        String name;        // Name of the directive
        String payload; // Payload for the directive (can be empty)
    } directive;           // Directive object containing name and payload
    
    // Constructor
    ActionMapping(std::vector<AlexaActions> actions, String directiveName, String directivePayload="{}")
        : actions(actions) {
        directive.name = directiveName;
        directive.payload = directivePayload;
    }



    // Get the JSON representation of ActionMapping
    JsonDocument getJSON() {
        JsonDocument doc;
        doc["@type"] = type;
        
        // Convert actions array to strings
        JsonArray actionArray = doc["actions"].to<JsonArray>();
        for (const auto& action : actions) {
            actionArray.add(AlexaActionsUtils::toString(action));
        }

        JsonObject directiveObj = doc["directive"].to<JsonObject>();
        directiveObj["name"] = directive.name;
        if (directive.payload) {
            directiveObj["payload"] = directive.payload;
        }
        return doc;
    }
};



// AlexaInterface class definition
class AlexaInterface
{
private:
    AlexaInterfaceType type;
    bool retrievable;
    bool proactivelyReported;
    std::vector<ActionMapping> actionMappings;  // Array of ActionMappings
    std::vector<FriendlyName> friendlyNames;  // Array of FriendlyNames


    String instance;
    bool nameSet;
public:
    // Constructor
    AlexaInterface(AlexaInterfaceType type, bool retrievable = true, bool proactivelyReported = false)
        : type(type), retrievable(retrievable), proactivelyReported(proactivelyReported) {}

    // Getters
    AlexaInterfaceType getType() const { return type; }
    String getTypeString() const { return AlexaInterfaceUtils::toString(type); }
    String getVersion() const { return AlexaInterfaceUtils::getVersion(type); }
    std::vector<String> getProps() const { return AlexaInterfaceUtils::getProps(type); }

    void setInstance(const char* name){
        instance=name;
        nameSet=true;
    }

    void addFriendlyName(const char* name,const char* locale){
        friendlyNames.emplace_back(name,locale);
    }

    bool isRetrievable() const { return retrievable; }
    bool isProactivelyReported() const { return proactivelyReported; }

    // Setters
    void setRetrievable(bool value) { retrievable = value; }
    void setProactivelyReported(bool value) { proactivelyReported = value; }

    void addActionMapping(const ActionMapping& actionMapping) {
        actionMappings.push_back(actionMapping);
    }

    JsonDocument getJSON()
    {
        JsonDocument doc;
        String ret;

        // Set base properties
        doc["interface"] = getTypeString();
        doc["version"] = getVersion();
        doc["type"] = "AlexaInterface";

        // Add properties
        JsonObject properties = doc["properties"].to<JsonObject>();
        properties["retrievable"] = retrievable;
        properties["proactivelyReported"] = proactivelyReported;

        std::vector<String> props = getProps();

        JsonArray supported = properties["supported"].to<JsonArray>();
        int index = 0;
        for (String prop : props)
        {
            supported[index]["name"] = prop;
            index++;
        }


        JsonObject semantics = doc["semantics"].to<JsonObject>();

        // Add action mappings
        JsonArray actionMappingArray = semantics["actionMappings"].to<JsonArray>();
        for (ActionMapping& actionMapping : actionMappings) {
            actionMappingArray.add(actionMapping.getJSON().as<JsonObject>());
        }
        if(nameSet){
            doc["instance"]=instance;
        }


        // Add capabilityResources if friendlyNames is not empty
        if (!friendlyNames.empty()) {
            JsonObject capabilityResources = doc.createNestedObject("capabilityResources");
            JsonArray friendlyNamesArray = capabilityResources.createNestedArray("friendlyNames");

            for (const FriendlyName& fn : friendlyNames) {
                JsonObject friendlyNameObj = friendlyNamesArray.createNestedObject();
                friendlyNameObj["@type"] = "text";

                JsonObject valueObj = friendlyNameObj.createNestedObject("value");
                valueObj["text"] = fn.text;
                valueObj["locale"] = fn.locale;
            }
        }
        
        doc.shrinkToFit();
        return doc;
    }
};

#endif // ALEXA_INTERFACE_H
