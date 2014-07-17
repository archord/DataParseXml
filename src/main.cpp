/* 
 * File:   main.cpp
 * Author: xy
 *
 * Created on June 23, 2014, 4:08 PM
 */

#include <iostream>
#include "ParaConfig.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
  
  ParaConfig pc;
  pc.setConfFile("src/ParaConfig.xml");
  pc.readConfigFile();
  pc.showElements();
  pc.showEnums();
  pc.showTables();
  pc.showFormulas();
  
  return 0;
}

