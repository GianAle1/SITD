-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema SITD
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema SITD
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `SITD` DEFAULT CHARACTER SET utf8 ;
USE `SITD` ;

-- -----------------------------------------------------
-- Table `SITD`.`Usuario`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `SITD`.`Usuario` (
  `ID_Solictud` INT NOT NULL,
  `primer_nombre` VARCHAR(20) NOT NULL,
  `segundo_nombre` VARCHAR(20) NOT NULL,
  `primer_Apellido` VARCHAR(20) NOT NULL,
  `segundo_Apellido` VARCHAR(45) NOT NULL,
  `fecha` DATE NOT NULL,
  `lugar_Nac` VARCHAR(50) NOT NULL,
  `nacionalidad` VARCHAR(10) NOT NULL,
  `direccion` VARCHAR(50) NOT NULL,
  `sexo` VARCHAR(1) NOT NULL,
  `estado` VARCHAR(1) NOT NULL,
  PRIMARY KEY (`ID_Solictud`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `SITD`.`DNI`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `SITD`.`DNI` (
  `N_dni` INT NOT NULL,
  `ID_Solictud_2` INT NOT NULL,
  PRIMARY KEY (`N_dni`),
  INDEX `fk_DNI_Usuario_idx` (`ID_Solictud_2` ASC) VISIBLE,
  CONSTRAINT `fk_DNI_Usuario`
    FOREIGN KEY (`ID_Solictud_2`)
    REFERENCES `SITD`.`Usuario` (`ID_Solictud`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
