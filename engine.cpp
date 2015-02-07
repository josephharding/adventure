
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

#include "engine.h"
#include "helper.h"

std::stringstream Engine::getChoiceDisplay() {
    std::stringstream ss;
    ss << "{\"choiceindex\": \"" << lastChoiceIndex << "\", \"choicetext\": \"" << choices[lastChoiceIndex].text << "\",";
    ss << "\"options\": [";
    unsigned long len = (unsigned long) choices[lastChoiceIndex].options.size();
    for(int i = 0; i < len; i++) {
        ss << "\"" << choices[lastChoiceIndex].options[i].text << "\"";
        if(i != len - 1) {
          ss << ",";
        }
    }
    ss << "]}";
    return ss;
}

std::string Engine::handleBegin() {
  lastChoiceIndex = 0;
  return Engine::getChoiceDisplay().str();
}

std::string Engine::handleOptionSelection(int choiceIndex, int optionIndex) {
  lastChoiceIndex = choices[choiceIndex].options[optionIndex].choiceIndex;
  return Engine::getChoiceDisplay().str();
}

std::string Engine::handleMessage(std::string message) {
  std::vector<std::string> split_message = split(message, ',');

  int choiceIndex = parseInt(split_message[0]);
  int optionIndex = parseInt(split_message[1]);

  // if the option index is -1 then we are just starting and have not selected an option yet
  std::string output;
  if(optionIndex == -1) {
    output = handleBegin();
  } else {
    output = handleOptionSelection(choiceIndex, optionIndex);
  }
  return output;
}

Engine::Engine() {
    
    // read in properties file - need to figure out how to package this up better
    std::ifstream infile("strings.properties");
    std::string line;
    while (getline(infile, line)) {
        std::vector<std::string> lineVec = split(line, '=');
        propMap[lineVec[0]] = lineVec[1];
    }
   
    choices[0] = {propMap["choice0"], {{propMap["option0_0"], 1}, {propMap["option0_1"], 2}, {propMap["option0_2"], 3}}};
    choices[1] = {propMap["choice1"], {{propMap["option1_0"], 0}, {propMap["option1_1"], 3}}};
    choices[2] = {propMap["choice2"], {{propMap["option1_0"], 0}, {propMap["option1_1"], 3}}};
    choices[3] = {propMap["choice3"], {{}, {}}};
}
