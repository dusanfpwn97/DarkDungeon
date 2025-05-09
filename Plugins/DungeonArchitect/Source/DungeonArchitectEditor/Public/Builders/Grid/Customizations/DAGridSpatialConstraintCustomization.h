//$ Copyright 2015-20, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "IPropertyTypeCustomization.h"
#include "Input/Reply.h"
#include "PropertyHandle.h"

class FDAGridConstraintCustomizationBase : public IPropertyTypeCustomization {
public:

    /**
    * Called when the header of the property (the row in the details panel where the property is shown)
    * If nothing is added to the row, the header is not displayed
    *
    * @param PropertyHandle			Handle to the property being customized
    * @param HeaderRow					A row that widgets can be added to
    * @param StructCustomizationUtils	Utilities for customization
    */
    void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow,
                         IPropertyTypeCustomizationUtils& CustomizationUtils) override;

    /**
    * Called when the children of the property should be customized or extra rows added
    *
    * @param PropertyHandle			Handle to the property being customized
    * @param StructBuilder				A builder for adding children
    * @param StructCustomizationUtils	Utilities for customization
    */
    void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder,
                           IPropertyTypeCustomizationUtils& CustomizationUtils) override;

    FReply OnCellClicked(int32 index);
    FText GetButtonText(int32 index) const;

protected:
    TArray<UObject*> GetSelectedObjects(IDetailLayoutBuilder& DetailBuilder);

    virtual void CreateWidget(FDetailWidgetRow& HeaderRow) = 0;

    TSharedPtr<IPropertyHandle> GetCellElement(uint32 index) const;
    TSharedPtr<IPropertyHandle> GetCellConstraintElement(uint32 index) const;


    FText GetConstraintName(uint8 value) const;

protected:
    /** Pointer to the string that will be set when changing the path */
    TSharedPtr<IPropertyHandle> CellDataProperty;
};


class FDAGridConstraintCustomization3x3 : public FDAGridConstraintCustomizationBase {
public:
    static TSharedRef<IPropertyTypeCustomization> MakeInstance();
    void CreateWidget(FDetailWidgetRow& HeaderRow) override;

};


class FDAGridConstraintCustomization2x2 : public FDAGridConstraintCustomizationBase {
public:
    static TSharedRef<IPropertyTypeCustomization> MakeInstance();
    void CreateWidget(FDetailWidgetRow& HeaderRow) override;

};

class FDAGridConstraintCustomizationEdge : public FDAGridConstraintCustomizationBase {
public:
    static TSharedRef<IPropertyTypeCustomization> MakeInstance();
    void CreateWidget(FDetailWidgetRow& HeaderRow) override;

};
