/* 
 * File:   ParaConfig.h
 * Author: xy
 *
 * Created on July 4, 2014, 5:02 PM
 */

#ifndef PARACONFIG_H
#define	PARACONFIG_H

#include <string>
#include <list>
#include <map>

#include "Markup.h"

using namespace std;

typedef union RangeType {
  int intType;
  float floatType;
} RANGETYPE;

class Element {
public:
  string name;
  string type;
  string unit;
  int length;
  int downChannel;
  string showType;
  string formate;
  string operation;
  string opObject;
  bool isfloat;
  RANGETYPE valueRangeUp;
  RANGETYPE valueRangeDown;
  RANGETYPE alertRangeUp;
  RANGETYPE alertRangeDown;
  float samplingRate;
  
  list<Element> subElms;
  
  void getValues(CMarkup xmlNode);
  void showValue();
};

class ParaConfig {
public:
  string confFile;
  string objFile;
  
  CMarkup confXml;
  
  int totalElm;
  int totalLen;
  list<Element> elements;
  map<string, map<string, string> > enums;
  map<string, map<string, string> > tables;
  map<string, string> formulas;

  ParaConfig();
  ParaConfig(const ParaConfig& orig);
  virtual ~ParaConfig();
  
  /*初始化，如配置文件路径，代解析目标文件路径*/
  void init();
  void setConfFile(string confFile);
  void setObjFile(string objFile);
  
  /*读取配置文件信息*/
  bool readConfigFile();
  void readTotalElm();
  void readTotalLen();
  void readElements();
  void readEnums();
  void readTables();
  void readFormulas();
  void readOthers();
  void showElements();
  void showEnums();
  void showTables();
  void showFormulas();
  void showOthers();
  
  /*验证配置文件信息*/
  bool verifyElementsProperty();
  bool verifyType(Element elm);
  bool verifyLength(Element elm);
  bool verifyShowType(Element elm);
  bool verifyOperation(Element elm);
  
  /*根据配置文件解析目标文件*/
  bool readObjectFile();
  bool parseValues();
  
  /*检查目标文件解析结果是否符合配置文件需求，取值范围*/
  bool checkValues();
private:

};

#endif	/* PARACONFIG_H */

