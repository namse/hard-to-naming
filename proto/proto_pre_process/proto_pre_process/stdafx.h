#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <locale> 
#include <algorithm>
#include <cctype>

std::string ToUppercaseUnderscore(std::string target);
std::string ToLowercaseUnderscore(std::string target);