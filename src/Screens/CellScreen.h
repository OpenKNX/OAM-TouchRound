#pragma once

#include <functional>

#include "Screens/ICellObject.h"
#include "Screens/ICellScreen.h"
#include "Screen.h"

class CellObject;

class CellScreen: public Screen, public ICellScreen
{
public:
    virtual ICellObject& getCell(uint8_t index) = 0;
    virtual void show() override;
};

enum CellLocation
{
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
    Top,
    Bottom
};

class CellObject : public ICellObject
{
    CellScreen& _cellPage;
    lv_coord_t _width;
    lv_coord_t _height;
    lv_obj_t* _cell;
    lv_obj_t* _label;
    lv_obj_t* _value;
    lv_obj_t* _image;
    std::function<void()> _onPressed;
    std::function<void()> _onClicked;

    static void OnPressed(lv_event_t* e);
    static void OnClicked(lv_event_t* e);
public:
    CellObject(CellScreen& cellPage, lv_coord_t width, lv_coord_t height, CellLocation cellLocation);

    void SetPlacement(lv_align_t align, lv_coord_t x, lv_coord_t y);

    virtual void SetLabelText(const char* text) override;
    virtual void SetValueText(const char* text) override;
    virtual void SetImage(const char* imageFile, bool allowRecolor = false, bool active = false) override;
    virtual void ClearImage() override;
    virtual void SetImageState(bool active) override;
    virtual void RegisterPressed(std::function<void()> callback) override;
    virtual void RegisterClicked(std::function<void()> callback) override;
};


class CellScreen2: public CellScreen
{
public:
    static CellScreen2* instance;
    CellObject cellObject1;
    CellObject cellObject2;
    CellScreen2();
    virtual ICellObject& getCell(uint8_t index) override;
};

class CellScreen3 : public CellScreen
{
public:
    static CellScreen3* instance;
    CellObject cellObject1;
    CellObject cellObject2;
    CellObject cellObject3;
    CellScreen3();
    virtual ICellObject& getCell(uint8_t index) override;
};

class CellScreen4: public CellScreen
{
public:
    static CellScreen4* instance;
    CellObject cellObject1;
    CellObject cellObject2;
    CellObject cellObject3;
    CellObject cellObject4;
    CellScreen4();
    virtual ICellObject& getCell(uint8_t index) override;
};


