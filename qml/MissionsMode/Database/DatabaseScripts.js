var listDelegate;
var itemsArray = [];
var widthOfElement;//in pixels
var heightOfElement;//in pixels
var width;//in pixels
var height;//in pixels
var actualAmountOfItems = 0;
var yAtTop = 0;

function setupList(amountOfItems, widthInPx, heightInPx)
{
    yAtTop = 0;
    actualAmountOfItems = 0;
    widthOfElement = 540;
    heightOfElement = 732;
    width = widthInPx;
    height = heightInPx;
    for (var i=0;i<itemsArray.length;++i)
        itemsArray[i].destroy();
    listDelegate = Qt.createComponent("qrc:/qml/MissionsMode/Database/DatabaseEntry.qml");
    if (listDelegate == null) {
        console.log("Error creating object");
    }
    itemsArray = new Array(amountOfItems);
}

function setItem(index, name, art) {
    itemsArray[index].setArtSource(art);
    itemsArray[index].setName(name);
}

function createItem(name, art) {
    if (actualAmountOfItems < itemsArray.length)
    {
        var y00 = yAtTop;//not binded for sure
        itemsArray[actualAmountOfItems] = listDelegate.createObject(listHandler,
                                                {"x": actualAmountOfItems%2 == 0 ? 0 : widthOfElement,
                                                "y": actualAmountOfItems%2 == 0 ? actualAmountOfItems/2 * heightOfElement + y00 : (actualAmountOfItems-1)/2 * heightOfElement + y00,
                                                "width": width, "height": heightOfElement});
        setItem(actualAmountOfItems, name, art);
        ++actualAmountOfItems;
    }
}

function getClickedItemName(x,y) {
    var h = heightOfElement;
    var y0 = 0;
    var y1 = h - 1;
    y -= yAtTop;
    for (var i=0;i<actualAmountOfItems/2;++i)
    {
        if (y >= y0 && y <= y1)
            return itemsArray[x<widthOfElement ? i : i+1].getName();
        y0 += h;
        y1 += h;
    }

    return "";
}

function scrollList(y) {
    var amountOfRows = actualAmountOfItems%2 == 0 ? actualAmountOfItems/2 : (actualAmountOfItems+1)/2;
    if (amountOfRows*heightOfElement>height)
    {
        if (yAtTop + y > 0)//up
        {
            for (var i=0;i<actualAmountOfItems;++i)
                itemsArray[i].y -= yAtTop;
            yAtTop = 0;
        }
        else if (height - yAtTop - y >= amountOfRows * heightOfElement)//down
        {
            for (i=0;i<actualAmountOfItems;++i)
                itemsArray[i].y -= amountOfRows * heightOfElement + yAtTop - height;
            yAtTop =  height - amountOfRows * heightOfElement;
        }
        else
        {
            for (i=0;i<actualAmountOfItems;++i)
                itemsArray[i].y += y;
            yAtTop += y;
        }
    }
}
