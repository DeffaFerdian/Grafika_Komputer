-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Nov 23, 2021 at 05:00 AM
-- Server version: 10.4.21-MariaDB
-- PHP Version: 8.0.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `test`
--

-- --------------------------------------------------------

--
-- Table structure for table `mahasiwa`
--

CREATE TABLE `mahasiwa` (
  `id` int(11) NOT NULL,
  `nim` varchar(255) NOT NULL,
  `nama_lengkap` varchar(255) NOT NULL,
  `kota_asal` varchar(255) NOT NULL,
  `tanggal_lahir` varchar(255) NOT NULL,
  `nama_orangtua` varchar(255) NOT NULL,
  `alamat_orangtua` varchar(255) NOT NULL,
  `kode_pos` varchar(255) NOT NULL,
  `nomor_telepon` varchar(255) NOT NULL,
  `status` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `mahasiwa`
--

INSERT INTO `mahasiwa` (`id`, `nim`, `nama_lengkap`, `kota_asal`, `tanggal_lahir`, `nama_orangtua`, `alamat_orangtua`, `kode_pos`, `nomor_telepon`, `status`) VALUES
(1, '672019023', 'Panca Perkasa', 'Tanjung Pandan', '01 November 2001', 'Merli Warman', 'Bekasi', '402132', '082278401559', 'Tama');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `mahasiwa`
--
ALTER TABLE `mahasiwa`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `mahasiwa`
--
ALTER TABLE `mahasiwa`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
