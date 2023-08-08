#include "FieldParser.h"
#include <iostream>
#include <iomanip>

bool FieldParser::getDataFromXML(FieldBuilder& builder) {

    TiXmlDocument doc("input.xml");
    if (doc.LoadFile()) {
        TiXmlElement* root = doc.FirstChildElement("data");
  
        TiXmlElement* field = root->FirstChildElement("placement_zone")->FirstChildElement("rect");
        TiXmlElement* minPoint = field->FirstChildElement();
        double xMin, yMin, xMax, yMax;
        Coord min, max;
        if (minPoint->QueryDoubleAttribute("x", &xMin) == TIXML_SUCCESS && minPoint->QueryDoubleAttribute("y", &yMin) == TIXML_SUCCESS) {
            min.SetCoord(xMin, yMin);
        }
        TiXmlElement* maxPoint = minPoint->NextSiblingElement();
        if (maxPoint->QueryDoubleAttribute("x", &xMax) == TIXML_SUCCESS && maxPoint->QueryDoubleAttribute("y", &yMax) == TIXML_SUCCESS) {
            max.SetCoord(xMax, yMax);
        }
        if (builder.setField(RectByCoords(min, max))) std::cout << "Поле задано\n";
          
        TiXmlElement* alarms = field->NextSiblingElement("alarms");
        TiXmlElement* alarm = alarms->FirstChildElement("alarms");
        for (TiXmlElement* alarm = alarms->FirstChildElement(); alarm != nullptr; alarm = alarm->NextSiblingElement("alarms")) {
            TiXmlElement* minPoint = alarm->FirstChildElement();
            double xMin, yMin, xMax, yMax;
            Coord min, max;
            if (minPoint->QueryDoubleAttribute("x", &xMin) == TIXML_SUCCESS && minPoint->QueryDoubleAttribute("y", &yMin) == TIXML_SUCCESS) {
                min.SetCoord(xMin, yMin);
            }
            TiXmlElement* maxPoint = minPoint->NextSiblingElement();
            if (maxPoint->QueryDoubleAttribute("x", &xMax) == TIXML_SUCCESS && maxPoint->QueryDoubleAttribute("y", &yMax) == TIXML_SUCCESS) {
                max.SetCoord(xMax, yMax);
            }
            if (builder.setObstruction(Obstruction(RectByCoords(min, max)))) std::cout << "Препятствие добавленo\n";
        }

        TiXmlElement* circles = root->FirstChildElement()->NextSiblingElement("circles");
        for (TiXmlElement* circle = circles->FirstChildElement(); circle != nullptr; circle = circle->NextSiblingElement("circle")) {
            int id;
            double inR, outR;
            if (circle->QueryIntAttribute("id", &id) == TIXML_SUCCESS && circle->QueryDoubleAttribute("inner_rad", &inR) == TIXML_SUCCESS &&
                circle->QueryDoubleAttribute("outter_rad", &outR) == TIXML_SUCCESS) {
                Bolt bolt(DoubleCircle(inR, outR), id);
                if (builder.addBolt(bolt)) std::cout << "Болт добавлен\n";
            }
        }
        return true;
    }
    return false;
}

bool FieldParser::putDataToXML(const vector<Bolt>& bolts) {
    TiXmlDocument doc;
    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "UTF-8", "");
    doc.LinkEndChild(decl);

    auto* root = new TiXmlElement("data");
    doc.LinkEndChild(root);

    TiXmlComment* comment = new TiXmlComment();
    comment->SetValue(" Положения кругов ");
    root->LinkEndChild(comment);

    auto* circles = new TiXmlElement("circles");
    root->LinkEndChild(circles);

    for (int i = 0; i < bolts.size(); i++) {
        auto* circle = new TiXmlElement("circle");
        circles->LinkEndChild(circle);
        circle->SetAttribute("id", std::to_string(bolts[i].getID()));
        circle->SetAttribute("x", std::to_string(bolts[i].getCenter().getX()));
        circle->SetAttribute("y", std::to_string(bolts[i].getCenter().getY()));
    }

    return doc.SaveFile("output.xml");
}