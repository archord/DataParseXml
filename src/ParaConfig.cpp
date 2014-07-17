/* 
 * File:   ParaConfig.cpp
 * Author: xy
 * 
 * Created on July 4, 2014, 5:02 PM
 */

#include <iostream>
#include "ParaConfig.h"

void Element::getValues(CMarkup xmlNode) {

  string tStr = xmlNode.GetAttrib("name");
  name = tStr;
  tStr = xmlNode.GetAttrib("type");
  type = tStr;
  tStr = xmlNode.GetAttrib("unit");
  unit = tStr;
  tStr = xmlNode.GetAttrib("length");
  if (!tStr.empty()) {
    length = atoi(tStr.c_str());
  } else {
    length = 0;
  }
  tStr = xmlNode.GetAttrib("downChannel");
  if (!tStr.empty()) {
    downChannel = atoi(tStr.c_str());
  } else {
    downChannel = 0;
  }
  tStr = xmlNode.GetAttrib("showType");
  showType = tStr;
  tStr = xmlNode.GetAttrib("formate");
  formate = tStr;
  tStr = xmlNode.GetAttrib("operation");
  operation = tStr;
  tStr = xmlNode.GetAttrib("opObject");
  opObject = tStr;
  tStr = xmlNode.GetAttrib("valueRangeUp");
  isfloat = false;
  if (!tStr.empty()) {
    if (tStr.find('.') >= 0) {
      isfloat = true;
      valueRangeUp.floatType = atof(tStr.c_str());
    } else
      valueRangeUp.intType = atoi(tStr.c_str());
  } else {
    valueRangeUp.intType = 0;
  }
  tStr = xmlNode.GetAttrib("valueRangeDown");
  if (!tStr.empty()) {
    if (tStr.find('.') >= 0) {
      isfloat = true;
      valueRangeDown.floatType = atof(tStr.c_str());
    } else
      valueRangeDown.intType = atoi(tStr.c_str());
  } else {
    valueRangeDown.intType = 0;
  }
  tStr = xmlNode.GetAttrib("alertRangeUp");
  if (!tStr.empty()) {
    if (tStr.find('.') >= 0) {
      isfloat = true;
      alertRangeUp.floatType = atof(tStr.c_str());
    } else
      alertRangeUp.intType = atoi(tStr.c_str());
  } else {
    alertRangeUp.intType = 0;
  }
  tStr = xmlNode.GetAttrib("alertRangeDown");
  if (!tStr.empty()) {
    if (tStr.find('.') >= 0) {
      isfloat = true;
      alertRangeDown.floatType = atof(tStr.c_str());
    } else
      alertRangeDown.intType = atoi(tStr.c_str());
  } else {
    alertRangeDown.intType = 0;
  }
  tStr = xmlNode.GetAttrib("samplingRate");
  if (!tStr.empty()) {
    samplingRate = atof(tStr.c_str());
  } else {
    samplingRate = 0;
  }
}

void Element::showValue() {
  cout << name
          << ", " << type
          << ", " << unit
          << ", " << length
          << ", " << downChannel
          << ", " << showType
          << ", " << formate
          << ", " << operation
          << ", " << opObject;
  if (isfloat) {
    cout << ", " << valueRangeUp.floatType
            << ", " << valueRangeDown.floatType
            << ", " << alertRangeUp.floatType
            << ", " << alertRangeDown.floatType;
  } else {
    cout << ", " << valueRangeUp.intType
            << ", " << valueRangeDown.intType
            << ", " << alertRangeUp.intType
            << ", " << alertRangeDown.intType;
  }
  cout << ", " << samplingRate
          << endl;
}

ParaConfig::ParaConfig() {
  init();
}

ParaConfig::ParaConfig(const ParaConfig& orig) {
}

ParaConfig::~ParaConfig() {
}

/*初始化，如配置文件路径，代解析目标文件路径*/
void ParaConfig::init() {

  totalElm = 0;
  totalLen = 0;

  //  confFile = NULL;
  //  objFile = NULL;
  //  confXml = NULL;
  //  elements = NULL;
  //  enums = NULL;
  //  tables = NULL;
  //  formulas = NULL;
}

void ParaConfig::setConfFile(string confFile) {
  this->confFile = confFile;
}

void ParaConfig::setObjFile(string objFile) {
  this->objFile = objFile;
}

/*读取配置文件信息*/
bool ParaConfig::readConfigFile() {

  if (!confFile.empty()) {
    bool bLoadResult = confXml.Load(confFile);
    if (!bLoadResult) {
      cout << "Open " + confFile + " error!" << endl;
      cout << "Error message: " + confXml.GetError() << endl;
      return false;
    }
  } else {
    cout << "configure file name is empty!" << endl;
    return false;
  }

  readTotalElm();
  readTotalLen();
  readElements();
  readEnums();
  readTables();
  readFormulas();
  readOthers();

  return true;
}

void ParaConfig::readTotalElm() {
  if (confXml.FindChildElem("totalElm")) {
    confXml.IntoElem();
    string tStr = confXml.GetAttrib("value");
    confXml.OutOfElem();
  } else {
    cout << "no element named totalElm" << endl;
  }
}

void ParaConfig::readTotalLen() {
  if (confXml.FindChildElem("totalLen")) {
    confXml.IntoElem();
    string tStr = confXml.GetAttrib("value");
    confXml.OutOfElem();
  } else {
    cout << "no element named totalLen" << endl;
  }
}

void ParaConfig::readElements() {
  while (confXml.FindChildElem("element")) {
    confXml.IntoElem();
    Element telement;
    telement.getValues(confXml);
    if (telement.type.compare("complexType") == 0) {
      while (confXml.FindChildElem("subElm")) {
        confXml.IntoElem();
        Element subelm;
        subelm.getValues(confXml);
        confXml.OutOfElem();
        telement.subElms.push_back(subelm);
      }
    }
    confXml.OutOfElem();
    elements.push_back(telement);
  }
  if (elements.empty()) {
    cout << "no element found" << endl;
  }
}

void ParaConfig::showElements() {

  cout << "************show all element" << endl;
  for (list<Element>::iterator im = elements.begin(); im != elements.end(); ++im) {
    im->showValue();
    if (im->type.compare("complexType") == 0) {
      for (list<Element>::iterator im2 = im->subElms.begin(); im2 != im->subElms.end(); ++im2) {
        im2->showValue();
      }
    }
  }
}

void ParaConfig::readEnums() {

  while (confXml.FindChildElem("enum")) {
    confXml.IntoElem();
    string enumName = confXml.GetAttrib("name");

    map<string, string> tpair;
    while (confXml.FindChildElem("pair")) {
      confXml.IntoElem();
      string key = confXml.GetAttrib("key");
      string value = confXml.GetAttrib("value");
      tpair.insert(pair<string, string>(key, value));
      confXml.OutOfElem();
    }
    enums.insert(pair<string, map<string, string> >(enumName, tpair));
    confXml.OutOfElem();
  }
  if (enums.empty()) {
    cout << "no enum found" << endl;
  }
}

void ParaConfig::showEnums() {
  
  cout << "************show all enum" << endl;
  for (map<string, map<string, string> >::iterator mi = enums.begin();
          mi != enums.end(); mi++) {
    cout << "enum name: " << mi->first << endl;
    for (map<string, string>::iterator mi2 = mi->second.begin();
            mi2 != mi->second.end(); mi2++) {
      cout << "  key:" << mi2->first << " value:" << mi2->second << endl;
    }
  }
}

void ParaConfig::readTables() {

  while (confXml.FindChildElem("table")) {
    confXml.IntoElem();
    string name = confXml.GetAttrib("name");
    string path = confXml.GetAttrib("path");
    string filename = confXml.GetAttrib("filename");
    map<string, string> tmap;
    tmap.insert(pair<string, string>(path, filename));
    tables.insert(pair<string, map<string, string> >(name, tmap));
    confXml.OutOfElem();
  }
  if (tables.empty()) {
    cout << "no table found" << endl;
  }
}

void ParaConfig::showTables() {
  
  cout << "************show all table" << endl;
  for (map<string, map<string, string> >::iterator mi = tables.begin();
          mi != tables.end(); mi++) {
    map<string, string>::iterator mi2 = mi->second.begin();
    cout << "table name: " << mi->first << "  key:" << mi2->first << " value:" << mi2->second << endl;
  }
}

void ParaConfig::readFormulas() {

  while (confXml.FindChildElem("formula")) {
    confXml.IntoElem();
    string name = confXml.GetAttrib("name");
    string value = confXml.GetAttrib("value");
    formulas.insert(pair<string, string>(name, value));
    confXml.OutOfElem();
  }
  if (formulas.empty()) {
    cout << "no formula found" << endl;
  }
}

void ParaConfig::showFormulas() {
  
  cout << "************show all formula" << endl;
  for (map<string, string>::iterator mi = formulas.begin();
          mi != formulas.end(); mi++) {
    cout << "formula name: " << mi->first << "  value:" << mi->second << endl;
  }
}

void ParaConfig::readOthers() {
}

void ParaConfig::showOthers() {
  
}

/*验证配置文件信息*/
bool ParaConfig::verifyElementsProperty() {
}

bool ParaConfig::verifyType(Element elm) {
}

bool ParaConfig::verifyLength(Element elm) {
}

bool ParaConfig::verifyShowType(Element elm) {
}

bool ParaConfig::verifyOperation(Element elm) {
}

/*根据配置文件解析目标文件*/
bool ParaConfig::readObjectFile() {
}

bool ParaConfig::parseValues() {
}

/*检查目标文件解析结果是否符合配置文件需求，取值范围*/
bool ParaConfig::checkValues() {
}
