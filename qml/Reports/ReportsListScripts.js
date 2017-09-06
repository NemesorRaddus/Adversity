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
    listDelegate = Qt.createComponent("qrc:/qml/Reports/ReportsListDelegate.qml");
    if (listDelegate == null) {
        console.log("Error creating object");
    }
    itemsArray = new Array(amountOfItems);
}

function setItem(index, text) {
    itemsArray[index].setText(text);
}

function createItem(text) {
    if (actualAmountOfItems < itemsArray.length)
    {
        var y00 = yAtTop;//not binded for sure
        itemsArray[actualAmountOfItems] = listDelegate.createObject(rootBuildingsList,
                                                {"x": 0,
                                                "y": actualAmountOfItems * heightOfElement + y00,
                                                "width": width, "height": heightOfElement});
        setItem(actualAmountOfItems,text);
        ++actualAmountOfItems;
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
