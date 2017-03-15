var listDelegate;
var itemsArray;
var heightOfElement;//in cm
var width;//in pixels
var height;//in pixels
var dpcm;
var actualAmountOfItems = 0;
var yAtTop = 0;

function setupList(heightOfElementInCm, windowDpcm, amountOfItems, widthInPx, heightInPx)
{
    heightOfElement = heightOfElementInCm;
    width = widthInPx;
    height = heightInPx;
    dpcm = windowDpcm;
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
                                                "y": actualAmountOfItems * heightOfElement * dpcm + y00,
                                                "width": width, "height": heightOfElement * dpcm});
        setItem(actualAmountOfItems,name,internalName,level,description);
        ++actualAmountOfItems;
    }
}

function getClickedItemName(y) {
    var h = heightOfElement * dpcm;
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
    if (yAtTop + y <= 0 && height - yAtTop - y < actualAmountOfItems * heightOfElement * dpcm)
    {
        for (var i=0;i<actualAmountOfItems;++i)
            itemsArray[i].y += y;
        yAtTop += y;
    }
}
