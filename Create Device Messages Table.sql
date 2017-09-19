CREATE TABLE `device_messages` (
  `iddevice_messages` int(11) NOT NULL AUTO_INCREMENT,
  `device_name` varchar(45) DEFAULT NULL,
  `datetime` datetime DEFAULT NULL,
  `temperature` float DEFAULT NULL,
  `humidity` float DEFAULT NULL,
  `analog_voltage` float DEFAULT NULL,
  `distance` int(11) DEFAULT NULL,
  PRIMARY KEY (`iddevice_messages`)
) ENGINE=InnoDB AUTO_INCREMENT=54461 DEFAULT CHARSET=utf8 COMMENT='Table for storing IoT device messages';
