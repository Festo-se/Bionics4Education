
const key_motor_position = "motor_position"
const key_brightness_threshold = "brightness_threshold"
const key_upper_brightness_threshold = "upper_brightness_threshold"
const key_lower_brightness_threshold = "lower_brightness_threshold"
const key_color = "color"
const key_is_autonomous = "is_autonomous"
const key_brightness = "brightness"
const key_touch_left = "touch_left"
const key_touch_right = "touch_right"
const key_alpha = "alpha"
const key_has_touch = "has_touch"
const key_has_light = "has_light"
const key_speed = "speed"

const id_slider_motor_position = "motor-position-slider"
const id_slider_brightness_threshold = "brightness-threshold-slider"
const id_slider_brightness_threshold_title = "brightness-threshold-slider-title"
const id_slider_speed = "speed-slider"
const id_color_picker = "color-picker"
const id_color_picker_manual = "color-picker-manual"
const id_indicator_has_touch = "has-touch-indicator"
const id_indicator_has_light = "has-light-indicator"
const id_indicator_touch_direction_image = "touch-direction-image"
const id_indicator_light_image = "light-image"
const id_tab_manual = "manual"
const id_tab_autonomous = "autonomous"
const id_slider_brightness_threshold_current_value = 'brightness-threshold-current-value-slider'
const id_slider_brightness_threshold_minmax = 'brightness-threshold-minmax-slider'

var upper_brightness_threshold = 100
var lower_brightness_threshold = 0
var min_measured_brightness = 100
var max_measured_brightness = 0
var current_measured_brightness = 0
var selected_color = '#0091DC'
var is_autonomous = false

var color_picker_is_open = true
var is_updating_from_web = false

$(document).ready(function () {
    $("#" + id_color_picker).attr('value', selected_color)
    $("#" + id_color_picker_manual).attr('value', selected_color)
    $(document).on('click', '.navbar-collapse.in', function (e) {
        if ($(e.target).is('a')) {
            $(this).collapse('hide');
        }
    })

    createSampleBrightnessThresholdSlider()

    var motor_position_slider = $("#" + id_slider_motor_position).slider({})
    var brightness_threshold_slider = $("#" + id_slider_brightness_threshold).slider({})
    var speed_slider = $("#" + id_slider_speed).slider({})
    var color_picker = $("#" + id_color_picker)

    color_picker.click(function () { color_picker_is_open = true })
    color_picker.change(function () { color_picker_is_open = false })

    color_picker.focusin(function () {
        if (color_picker_is_open) {
            color_picker_is_open = false
        }
    })

    $('#flower .slider').bind('slideStop', sendConfiguration)
    document.getElementById(id_color_picker).addEventListener('change', function (evt) {
        selected_color = $("#" + id_color_picker).val()
        sendConfiguration()
    }, false)
    document.getElementById(id_color_picker_manual).addEventListener('change', function (evt) {
        selected_color = $("#" + id_color_picker_manual).val()
        sendConfiguration()
    }, false)

    $('a[data-toggle="tab"]').on('shown.bs.tab', function (event) {
        var new_is_autonomous = $(event.target).text() == "Autonomous"
        if (is_autonomous == new_is_autonomous) {
            return
        }
        is_autonomous = new_is_autonomous
        sendConfiguration()
    })

    fetchConfiguration()
    setInterval(fetchSensorData, 1000)
})

function sendConfiguration() {
    if (is_updating_from_web) {
        return;
    }

    var motor_position = $("#" + id_slider_motor_position).slider('getValue') / 10
    var is_autonomous_value = is_autonomous ? 1 : 0
    var color = selected_color
    var speed = $("#" + id_slider_speed).slider('getValue') / 10
    var lower_brightness_threshold_value = $("#" + id_slider_brightness_threshold).slider('getValue')[0]
    var upper_brightness_threshold_value = $("#" + id_slider_brightness_threshold).slider('getValue')[1]

    document.getElementById("motor-position-slider-title").innerHTML = Math.ceil(Number(motor_position));
    document.getElementById("speed-slider-title").innerHTML = Math.ceil(Number(speed));

    $.post(
        "/configuration",
        jQuery.param({
            [key_motor_position]: motor_position,
            [key_speed]: speed,
            [key_lower_brightness_threshold]: lower_brightness_threshold_value,
            [key_upper_brightness_threshold]: upper_brightness_threshold_value,
            [key_is_autonomous]: is_autonomous_value,
            [key_color]: color
        }),
        readResponse
    )
}

function fetchConfiguration() {
    $.get("/configuration", readResponse)
}

function fetchSensorData() {
    $.get("/sensorData", readResponse)
}

function calibrate() {
    max_measured_brightness = current_measured_brightness
    min_measured_brightness = current_measured_brightness
    lower_brightness_threshold = current_measured_brightness - 20
    lower_brightness_threshold = (lower_brightness_threshold < 0) ? 0 : lower_brightness_threshold
    upper_brightness_threshold = current_measured_brightness + 20
    upper_brightness_threshold = (upper_brightness_threshold > 100) ? 100 : upper_brightness_threshold
    $("#" + id_slider_brightness_threshold)
        .slider('setValue', [Number(lower_brightness_threshold), Number(upper_brightness_threshold)])
    sendConfiguration()
}

function readResponse(data) {
    var configuration = {};
    String(data).split("&").forEach(function (string) {
        var keyValue = String(string).split("=")
        configuration[keyValue[0]] = keyValue[1]
    })
    updateUI(configuration)
}

function updateUI(configuration) {
    is_updating_from_web = true;

    var motor_position = configuration[key_motor_position]
    if (motor_position !== null) {
        $("#" + id_slider_motor_position)
            .slider('setValue', Number(motor_position) * 10, true)
    }

    var new_upper_brightness_threshold = configuration[key_upper_brightness_threshold]
    var new_lower_brightness_threshold = configuration[key_lower_brightness_threshold]
    if ((new_upper_brightness_threshold !== null) && (new_lower_brightness_threshold !== null)) {
        upper_brightness_threshold = new_upper_brightness_threshold
        lower_brightness_threshold = new_lower_brightness_threshold
        $("#" + id_slider_brightness_threshold)
            .slider('setValue', [Number(lower_brightness_threshold), Number(upper_brightness_threshold)])
    }

    var color = configuration[key_color]
    if (color !== null) {
        $("#" + id_color_picker).attr('value', color)
        $("#" + id_color_picker_manual).attr('value', color)
        if (!color_picker_is_open) {
            $("#" + id_color_picker).val(color)
            $("#" + id_color_picker).css("background-color", color)
            $("#" + id_color_picker_manual).css("background-color", color)
        }
    }

    var new_brightness = configuration[key_brightness]
    if (new_brightness !== null) {
        current_measured_brightness = Number(new_brightness)
        max_measured_brightness = current_measured_brightness > max_measured_brightness ? current_measured_brightness : max_measured_brightness
        min_measured_brightness = current_measured_brightness < min_measured_brightness ? current_measured_brightness : min_measured_brightness

        $("#" + id_slider_brightness_threshold_current_value)
            .slider('setValue', Number(current_measured_brightness))
        $("#" + id_slider_brightness_threshold_minmax)
            .slider('setValue', [Number(min_measured_brightness), Number(max_measured_brightness)])
    }

    var new_has_light = configuration[key_has_light]
    if (new_has_light !== null) {
        var color = (new_has_light == "1") ? "rgb(207,229,247)" : "#E1E5E8"
        $("#" + id_indicator_has_light).css("background-color", color)
        var image = (new_has_light == "1") ? "./images/EnableLightSensor.svg" : "./images/LightDisabledSensor.svg"
        $("#" + id_indicator_light_image).attr("src", image)
    }

    var new_has_touch = configuration[key_has_touch]
    if (new_has_touch !== null) {
        var color = (new_has_touch == "1") ? "rgb(207,229,247)" : "#E1E5E8"
        $("#" + id_indicator_has_touch).css("background-color", color)

        if (new_has_touch == "0") {
            $("#" + id_indicator_touch_direction_image).attr("src", "./images/TouchDisabledSensor.svg")
        } else if (configuration[key_touch_right] == "1") {
            $("#" + id_indicator_touch_direction_image).attr("src", "./images/UpperTouchSensor.svg")
        } else if (configuration[key_touch_left] == "1") {
            $("#" + id_indicator_touch_direction_image).attr("src", "./images/LowerTouchSensor.svg")
        } else {
            $("#" + id_indicator_touch_direction_image).attr("src", "./images/EnableTouchSensor.svg")
        }
    }

    var new_speed = configuration[key_speed]
    if (new_speed != null) {
        $("#" + id_slider_speed).slider('setValue', Number(new_speed) * 10, true)
    }

    is_updating_from_web = false;
}

function createSampleBrightnessThresholdSlider() {
    $("#" + id_slider_brightness_threshold).slider({
        id: "#brightnessHandlerSlider",
        min: 0,
        max: 100,
        value: [30, 70],
        focus: true
    })

    $("#" + id_slider_brightness_threshold_current_value).slider({
        id: 'current-brightness',
        min: 0,
        max: 100,
        value: 50,
        focus: true
    })

    $("#" + id_slider_brightness_threshold_minmax).slider({
        id: "minmax-brightness-threshold-slider",
        min: 0,
        max: 100,
        range: true,
        value: [20, 90],
        focus: true
    })
}