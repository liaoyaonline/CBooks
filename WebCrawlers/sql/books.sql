/*
 Navicat Premium Data Transfer

 Source Server         : hello
 Source Server Type    : MySQL
 Source Server Version : 50735
 Source Host           : localhost:3306
 Source Schema         : books

 Target Server Type    : MySQL
 Target Server Version : 50735
 File Encoding         : 65001

 Date: 09/09/2021 11:21:33
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for BookDone
-- ----------------------------
DROP TABLE IF EXISTS `BookDone`;
CREATE TABLE `BookDone` (
  `BookId` varchar(100) NOT NULL COMMENT '书本id和书单id',
  `BookName` varchar(100) NOT NULL COMMENT '小说名',
  `BookAuthor` varchar(100) NOT NULL COMMENT '小说作者',
  `BookWordCount` varchar(100) NOT NULL COMMENT '小说字数',
  `Bookstatus` varchar(100) NOT NULL COMMENT '小说更新状态',
  `BookUpdata` varchar(100) NOT NULL COMMENT '小说最近更新时间',
  `BookScore` float(5,2) DEFAULT NULL COMMENT '小说评分',
  `BookScoreCount` int(11) DEFAULT NULL COMMENT '小说评分人数',
  `OneStarRate` float(5,2) DEFAULT NULL COMMENT '一星评分占比',
  `TwoStarRate` float(5,2) DEFAULT NULL COMMENT '二星评分占比',
  `ThreeStarRate` float(5,2) DEFAULT NULL COMMENT '三星评分占比',
  `FourStarRate` float(5,2) DEFAULT NULL COMMENT '四星评分占比',
  `FiveStarRate` float(5,2) DEFAULT NULL COMMENT '五星评分占比',
  `BookClass` varchar(1000) NOT NULL COMMENT '小说类型偏向',
  `AddListCount` int(11) DEFAULT NULL COMMENT '加入书单数目',
  `BookIntro` varchar(20000) NOT NULL COMMENT '小说介绍',
  PRIMARY KEY (`BookId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for BooklistDone
-- ----------------------------
DROP TABLE IF EXISTS `BooklistDone`;
CREATE TABLE `BooklistDone` (
  `BooklistId` varchar(100) NOT NULL COMMENT '书单Id',
  `BooklistName` varchar(100) NOT NULL COMMENT '书单名',
  `BooklistAuthor` varchar(100) NOT NULL COMMENT '书单作者',
  `BooklistViews` varchar(100) NOT NULL COMMENT '书单观看人数',
  `BooklistCount` int(11) DEFAULT NULL COMMENT '书单内小说数目',
  `BooklistKeep` int(11) DEFAULT NULL COMMENT '收藏本书单人数',
  `BookType` varchar(1000) NOT NULL COMMENT '书单内小说类型',
  `BooklistUpdata` varchar(100) NOT NULL COMMENT '书单最近更新时间',
  `BooklistIntro` varchar(20000) NOT NULL COMMENT '书单介绍',
  PRIMARY KEY (`BooklistId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for ing
-- ----------------------------
DROP TABLE IF EXISTS `ing`;
CREATE TABLE `ing` (
  `BooksId` varchar(100) NOT NULL COMMENT '书本id和书单id',
  PRIMARY KEY (`BooksId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

SET FOREIGN_KEY_CHECKS = 1;
