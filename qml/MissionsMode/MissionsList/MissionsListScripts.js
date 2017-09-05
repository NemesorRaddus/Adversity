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
    widthOfElement = 1080;
    heightOfElement = 271;
    width = widthInPx;
    height = heightInPx;
    for (var i=0;i<itemsArray.length;++i)
        itemsArray[i].destroy();
    listDelegate = Qt.createComponent("qrc:/qml/MissionsMode/MissionsList/MissionsListDelegate.qml");
    if (listDelegate == null) {
        console.log("Error creating object");
    }
    itemsArray = new Array(amountOfItems);
}

function clearList()
{
    yAtTop = 0;
    actualAmountOfItems = 0;
    for (var i=0;i<itemsArray.length;++i)
        itemsArray[i].destroy();
    itemsArray = [];
}

function setItem(index, name, profession, art, land, length, daysSpent, signalOn, sbeOn, hp, hl, st, sl) {
    itemsArray[index].setName(name);
    itemsArray[index].setProfession(profession);
    itemsArray[index].setArtSource(art);
    itemsArray[index].setStatusFrames(hp,hl,st,sl);
    itemsArray[index].setMissionInfo(land,length,daysSpent,signalOn,sbeOn);
}

function createItem(name, profession, art, land, length, daysSpent, signalOn, sbeOn, hp, hl, st, sl) {
    if (actualAmountOfItems < itemsArray.length)
    {
        var y00 = yAtTop;//not binded for sure
        itemsArray[actualAmountOfItems] = listDelegate.createObject(listHandler,
                                                {"x": 0,
                                                "y": actualAmountOfItems * heightOfElement + y00,
                                                "width": width, "height": heightOfElement});
        setItem(actualAmountOfItems, name, profession, art, land, length, daysSpent, signalOn, sbeOn, hp, hl, st, sl);
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
            return itemsArray[i].getName();
        y0 += h;
        y1 += h;
    }

    return "";
}

function scrollList(y) {
    if (actualAmountOfItems*heightOfElement>height)
    {
        if (yAtTop + y > 0)//up
        {
            for (var i=0;i<actualAmountOfItems;++i)
                itemsArray[i].y -= yAtTop;
            yAtTop = 0;
        }
        else if (height - yAtTop - y >= actualAmountOfItems * heightOfElement)//down
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
}
