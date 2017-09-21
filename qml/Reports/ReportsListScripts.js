var listDelegate;
var itemsArray = [];
var heightsOfElements = [];//in pixels
var totalHeightOfElements = 0;
var width;//in pixels
var height;//in pixels
var actualAmountOfItems = 0;
var yAtTop = 0;

function setupList(amountOfItems, widthInPx, heightInPx)
{
    yAtTop = 0;
    actualAmountOfItems = 0;
    width = widthInPx;
    height = heightInPx;
    listDelegate = Qt.createComponent("qrc:/qml/Reports/ReportsListDelegate.qml");
    if (listDelegate == null) {
        console.log("Error creating object");
    }
    for (var i=0;i<itemsArray.length;++i)
        itemsArray[i].destroy();
    itemsArray = new Array(amountOfItems);
    heightsOfElements = new Array(amountOfItems);
    totalHeightOfElements = 0;
}

function setItem(index, time, text, art) {
    itemsArray[index].setText(time+"\n"+text);
    itemsArray[index].setArt(art);
}

function createItem(time, text, art) {
    if (actualAmountOfItems < itemsArray.length)
    {
        var y00 = yAtTop;//not binded for sure
        itemsArray[actualAmountOfItems] = listDelegate.createObject(reportsHandler,
                                                {"x": 0,
                                                "y": totalHeightOfElements + y00,
                                                "width": width});
        setItem(actualAmountOfItems,time,text,art);
        heightsOfElements[actualAmountOfItems] = itemsArray[actualAmountOfItems].getHeight();
        totalHeightOfElements+=heightsOfElements[actualAmountOfItems];
        ++actualAmountOfItems;
    }
}

function scrollList(y) {
    if (totalHeightOfElements>height)
    {
        if (yAtTop + y > 0)
        {
            for (var i=0;i<actualAmountOfItems;++i)
                itemsArray[i].y -= yAtTop;
            yAtTop = 0;
        }
        else if (height - yAtTop - y >= totalHeightOfElements)
        {
            for (i=0;i<actualAmountOfItems;++i)
                itemsArray[i].y -= totalHeightOfElements + yAtTop - height;
            yAtTop =  height - totalHeightOfElements;
        }
        else
        {
            for (i=0;i<actualAmountOfItems;++i)
                itemsArray[i].y += y;
            yAtTop += y;
        }
    }
}
