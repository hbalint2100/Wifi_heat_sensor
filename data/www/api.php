<?php

enum Sources {
    case SENSOR;
    case WIFI;
    case MQTT;
    case SYSTEM;
};

enum RequestType {
    case GET;
    case POST;
}

class Data {
    private Sources $type;
    public RequestType $reqType;

    function __construct() {
        if(isset($_GET['src'])) {
            $this->reqType = RequestType::GET;
            switch ($_GET['src']) {
                case 'sensor':
                    $this->type = Sources::SENSOR;
                    break;
                case 'wifi':
                    $this->type = Sources::WIFI;
                    break;
                case 'mqtt':
                    $this->type = Sources::MQTT;
                    break;
                case 'system':
                    $this->type = Sources::SYSTEM;
                    break;
                default:
                    $this->type = Sources::SYSTEM;
            }
        } else {
            $this->reqType = RequestType::POST;
        }
    }

    function get() {
        switch ($this->type) {
            case Sources::SENSOR:
                return $this->sensorData();
            case Sources::SYSTEM:
                return $this->systemData();
            case Sources::MQTT:
                return $this->mqttData();
            /*
            case Sources::WIFI:
            */
        }
    }

    function post() {
        return ['body' => 'success'];
    }

    function sensorData() {
        $type = 'all';
        if(isset($_GET['type']))
            $type = $_GET['type'];
        if($type == 'all')
            return ['temperature' => rand(-30,50), 'humidity' => rand(0,100)];
        else if($type == 'temperature')
            return ['temperature' => rand(-30,50)];
        else if($type == 'humidity')
            return ['humidity' => rand(0,100)];
    }

    function systemData() {
        return ['systemTime' =>  microtime(true)];
    }

    function mqttData() {
        $info = 'all';
        if(isset($_GET['info']))
            $info = $_GET['info'];
        if($info == 'all')
            return ['brokerIP' => '192.168.1.2', 'brokerPort' => 1883,
                'deviceName' => 'MockAPI', 'username' => 'Gipsz Jakab'];
        else if($info == 'brokerip')
            return ['brokerIP' => '192.168.1.2'];
        else if($info == 'brokerport')
            return ['brokerPort' => 1883];
        else if($info == 'devicename')
            return ['deviceName' => 'MockAPI'];
        else if($info == 'username')
            return ['username' => 'Gipsz Jakab'];
    }
};

header('Access-Control-Allow-Origin: *');
$data = new Data();
if($data->reqType == RequestType::GET)
    echo json_encode($data->get());
else
    echo json_encode($data->post());