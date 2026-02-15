#include "BitcoinExchange.hpp"
#include "utils.hpp"

BitcoinExchange::BitcoinExchange() { this->loadDatabase(DATA_FILE); }

BitcoinExchange::BitcoinExchange(const BitcoinExchange &rightSide) {
  this->data = rightSide.data;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rightSide) {
  if (this != &rightSide) {
    this->data = rightSide.data;
  }
  return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string &filename) {
  std::ifstream file(filename.c_str());
  if (!file.is_open()) {
    throw std::runtime_error("Error: Could not open file " + filename);
  }
  std::string line;
  std::getline(file, line);

  while (std::getline(file, line)) {
    size_t commaPos = line.find(',');
    if (commaPos == std::string::npos) {
      std::cerr << RED("Error: ") << YELLOW("Invalid line format: ") << line << std::endl;
      continue;
    }

    std::string date = line.substr(0, commaPos);
    std::string valueStr = line.substr(commaPos + 1);

    double value = std::atof(valueStr.c_str());
    this->data[date] = value;
  }
  file.close();
}

bool BitcoinExchange::inputValidation(std::istringstream &iss,
                                      std::string &date,
                                      std::string &valueStr) const {
  if (!(iss >> date)) {
    std::cerr << RED("Error: ") << YELLOW("bad input => ") << iss.str() << std::endl;
    return false;
  }

  if (!isValidDate(date)) {
    std::cerr << RED("Error: ") << YELLOW("bad input => ") << date << std::endl;
    return false;
  }

  std::string remaining;
  if (!std::getline(iss, remaining)) {
    std::cerr << RED("Error: ") << YELLOW("bad input => ") << date << std::endl;
    return false;
  }

  valueStr = skipPipe(remaining);
  if (valueStr.empty()) {
    std::cerr << RED("Error: ") << YELLOW("bad input => ") << date << std::endl;
    return false;
  }

  if (!isValidValue(valueStr)) {
    return false;
  }
  return true;
}

void BitcoinExchange::processInput(const std::string &inputFile) {
  std::ifstream file(inputFile.c_str());
  if (!file.is_open()) {
    throw std::runtime_error("Error: Could not open file " + inputFile);
  }

  std::string line;
  if (std::getline(file, line) && line.find("date") != std::string::npos) {
    // Header skipped
  } else {
    // First line is not a header, process it
    file.seekg(0);
  }

  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string date, valueStr;
    if (!inputValidation(iss, date, valueStr))
      continue;
    double value = atof(valueStr.c_str());
    std::map<std::string, double> closestDates = this->findClosestDate(date);
    if (closestDates.empty()) {
      std::cerr << RED("Error: ") << YELLOW("No data available for date ") << date << std::endl;
      continue;
    }
    std::map<std::string, double>::iterator it = closestDates.upper_bound(date);
    if (it != closestDates.begin())
      --it;
    double closestValue = it->second;
    double result = value * closestValue;
    std::cout << std::fixed << std::setprecision(2)
              << GREEN(date) << " => " << BLUE(value) << " = " << CYAN(result)
              << std::endl;
  }
  file.close();
}

std::map<std::string, double>
BitcoinExchange::findClosestDate(const std::string &date) const {
  std::map<std::string, double> result;
  std::map<std::string, double>::const_iterator it =
      this->data.lower_bound(date);
  if (it != this->data.end()) {
    result[it->first] = it->second;
  }
  if (it != this->data.begin()) {
    --it;
    result[it->first] = it->second;
  }
  return result;
}
