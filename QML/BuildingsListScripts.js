var listDelegate;
var itemsArray;
var heightOfElement;//in pixels
var width;//in pixels
var height;//in pixels
var actualAmountOfItems = 0;
var yAtTop = 0;

function setupList(heightOfElementInPx, amountOfItems, widthInPx, heightInPx)
{
    heightOfElement = heightOfElementInPx;
    width = widthInPx;
    height = heightInPx;
    listDelegate = Qt.createComponent("qrc:/qml/BuildingsListDelegate.qml");
    if (listDelegate == null) {
        console.log("Error creating object");
    }
    itemsArray = new Array(amountOfItems);
}

function setItem(index, name, internalName, level, description) {
    itemsArray[index].setArtSource("qrc:/graphics/Buildings/"+internalName+".png");
    itemsArray[index].setName(name);
    itemsArray[index].setLevel("Level: "+level);
    itemsArray[index].setDescription(description);
}

function createItem(name, internalName, level, description) {
    if (actualAmountOfItems < itemsArray.length)
    {
        var y00 = yAtTop;//not binded for sure
        itemsArray[actualAmountOfItems] = listDelegate.createObject(rootBuildingsList,
                                                {"x": 0,
                                                "y": actualAmountOfItems * heightOfElement + y00,
                                                "width": width, "height": heightOfElement});
        setItem(actualAmountOfItems,name,internalName,level,description);
        ++actualAmountOfItems;
    }
}

function getClickedItemName(y) {
    var h = heightOfElement;
    var y0 = 0;
    var y1 = h - 1;
    y -= yAtTop;
    for (var i=0;i<actualAmountOfItems;++i)
    {
        if (y >= y0 && y <= y1)
            return itemsArray[i].getName().text;
        y0 += h;
        y1 += h;
    }
}

function scrollList(y) {
    if (yAtTop + y > 0)
    {
        for (var i=0;i<actualAmountOfItems;++i)
            itemsArray[i].y -= yAtTop;
        yAtTop = 0;
    }
    else if (height - yAtTop - y >= actualAmountOfItems * heightOfElement)
    {
        for (i=0;i<actualAmountOfItems;++i)
            itemsArray[i].y -= actualAmountOfItems * heightOfElement + yAtTop - height;
        yAtTop =  height - actualAmountOfItems * heightOfElement;
    }
    else
    {
        for (i=0;i<actualAmountOfItems;++i)
            itemsArray[i].y += y;
        yAtTop += y;
    }
}

function setUpgradedStatus(name, isUpgraded)
{
    for (var i=0;i<actualAmountOfItems;++i)
        if (itemsArray[i].getName().text === name)
        {
            itemsArray[i].markAsUpgraded(isUpgraded);

            break;
        }
}
