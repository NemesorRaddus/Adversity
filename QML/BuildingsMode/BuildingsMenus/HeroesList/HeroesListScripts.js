var listDelegate;
var itemsArray = [];
var heightOfElement;//in pixels
var width;//in pixels
var height;//in pixels
var actualAmountOfItems = 0;
var yAtTop = 0;

function setupList(heightOfElementInPx, amountOfItems, widthInPx, heightInPx)
{
    yAtTop = 0;
    actualAmountOfItems = 0;
    heightOfElement = heightOfElementInPx;
    width = widthInPx;
    height = heightInPx;
    listDelegate = Qt.createComponent("qrc:/qml/BuildingsMode/BuildingsMenus/HeroesList/HeroesListDelegate.qml");
    if (listDelegate == null) {
        console.log("Error creating object");
    }
    for (var i=0;i<itemsArray.length;++i)
        itemsArray[i].destroy();
    itemsArray = new Array(amountOfItems);
}

function setItem(index, name, internalName, profession, ce, pr, cl) {
    itemsArray[index].setArtSource("qrc:/graphics/Mercs/"+profession+'/'+internalName+".png");
    itemsArray[index].setName(name);
    itemsArray[index].setProfession(profession);
    itemsArray[index].setCE(ce);
    itemsArray[index].setPR(pr);
    itemsArray[index].setCL(cl);
}

function createItem(name, internalName, profession, ce, pr, cl) {
    if (actualAmountOfItems < itemsArray.length)
    {
        var y00 = yAtTop;//not binded for sure
        itemsArray[actualAmountOfItems] = listDelegate.createObject(rootHeroesList,
                                                {"x": 0,
                                                "y": actualAmountOfItems * heightOfElement + y00,
                                                "width": width, "height": heightOfElement});
        setItem(actualAmountOfItems,name,internalName,profession,ce,pr,cl);
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

function getClickedItemName2(y) {
    var h = heightOfElement;
    var y0 = 0;
    var y1 = h - 1;
    y -= yAtTop;
    for (var i=0;i<actualAmountOfItems;++i)
    {
        if (y >= y0 && y <= y1)
            return itemsArray[i].getProfession().text;
        y0 += h;
        y1 += h;
    }
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
