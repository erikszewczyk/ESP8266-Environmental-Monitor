CREATE TABLE `transient_state` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `param` varchar(45) NOT NULL,
  `state` smallint(3) DEFAULT NULL,
  `last_update` datetime DEFAULT NULL,
  `description` varchar(64) DEFAULT NULL,
  PRIMARY KEY (`id`,`param`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
