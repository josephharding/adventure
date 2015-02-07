
#include <map>
#include <sstream>
#include <vector>

struct Option {
  std::string text;
  int choiceIndex;
};

struct Choice {
  std::string text;
  std::vector<Option> options;
};

class Engine {
  
  public:
    Engine();
    std::string handleMessage(std::string message);

  private:
    std::map<std::string, std::string> propMap;
    Choice choices[4];
    int lastChoiceIndex;

    std::string handleOptionSelection(int choiceIndex, int optionIndex);
    std::string handleBegin();
    std::stringstream getChoiceDisplay();

};
