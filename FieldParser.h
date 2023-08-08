#pragma once
#include "FieldBuilder.h"
#include "Geometry.h"
#include <tinyxml.h>
#pragma comment (lib, "tinyxml.lib")

class FieldParser {
public:
	bool getDataFromXML(FieldBuilder& builder);
	bool putDataToXML(const vector<Bolt>& bolts);
};