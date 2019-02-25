CREATE TABLE IF NOT EXISTS `Qgiv`.`transactions` (
  `idtransactions` INT(11) NOT NULL AUTO_INCREMENT,
  `amount` VARCHAR(45) NOT NULL,
  `status` VARCHAR(45) NOT NULL,
  `payment_type` VARCHAR(45) NOT NULL,
  `user_email` VARCHAR(45) NOT NULL,
  `timestamp` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idtransactions`))
ENGINE = InnoDB
AUTO_INCREMENT = 6
DEFAULT CHARACTER SET = latin1
