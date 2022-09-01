<?php

enum Sources {
    case SENSOR;
    case WIFI;
    case MQTT;
    case SYSTEM;
};

class Data {
    private Sources $type;

    function __construct() {
        if(isset($_GET['src'])) {
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
        }
    }

    function get() {
        switch ($this->type) {
            case Sources::SENSOR:
                return $this->sensorData();
            case Sources::SYSTEM:
                return $this->systemData();
            /*
            case Sources::WIFI:
            case Sources::MQTT:
            */
        }
    }

    function sensorData() {
        $type = 'all';
        if(isset($_GET['type'])) {
            $type = $_GET['type'];
        }
        if($type == 'all') {
            return ['temperature' => rand(-30,50), 'humidity' => rand(0,100)];
        }
        else if($type == 'temperature') {
            return ['temperature' => rand(-30,50)];
        }
        else if($type == 'humidity') {
            return ['humidity' => rand(0,100)];
        }
    }

    function systemData() {
        return ['systemtime' =>  microtime(true)];
    }
};

header('Access-Control-Allow-Origin: *');
$data = new Data();
echo json_encode($data->get());