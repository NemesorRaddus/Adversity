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
    for (var i=0;i<itemsArray.length;++i)
        itemsArray[i].destroy();
    listDelegate = Qt.createComponent("qrc:/qml/MissionsMode/MercenariesListDelegate.qml");
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

function setItem(index, name, internalName, profession, ce, pr, cl, hp, hpMax, st, sl, sr, sa, fc, bce, bpr, bcl, bhpMax, bsl, bsr, bsa, bfc)
{
    if (name == "")
        itemsArray[index].setEmpty();
    else
    {
        itemsArray[index].setArtSource("qrc:/graphics/Mercenaries/"+GlobalsCpp.alterNormalTextToInternal(profession)+'/'+internalName+".png");
        itemsArray[index].setName(name);
        itemsArray[index].setProfession(profession);
        itemsArray[index].setCE(ce);
        itemsArray[index].setPR(pr);
        itemsArray[index].setCL(cl);
        itemsArray[index].setHP(hp, hpMax);
        itemsArray[index].setST(st);
        itemsArray[index].setSR(sr);
        itemsArray[index].setSL(sl);
        itemsArray[index].setSA(sa);
        itemsArray[index].setFC(fc);

        if (hpMax == bhpMax)
            itemsArray[index].setColorHL("#568b56");
        else if (hpMax > bhpMax)
            itemsArray[index].setColorHL("#439b20");
        else
            itemsArray[index].setColorHL("#bf0000");

        if (sl == bsl)
            itemsArray[index].setColorSL("#568b56");
        else if (sl > bsl)
            itemsArray[index].setColorSL("#439b20");
        else
            itemsArray[index].setColorSL("#bf0000");

        if (ce == bce)
            itemsArray[index].setColorCE("#568b56");
        else if (ce > bce)
            itemsArray[index].setColorCE("#439b20");
        else
            itemsArray[index].setColorCE("#bf0000");

        if (pr == bpr)
            itemsArray[index].setColorPR("#568b56");
        else if (pr > bpr)
            itemsArray[index].setColorPR("#439b20");
        else
            itemsArray[index].setColorPR("#bf0000");

        if (cl == bcl)
            itemsArray[index].setColorCL("#568b56");
        else if (cl > bcl)
            itemsArray[index].setColorCL("#439b20");
        else
            itemsArray[index].setColorCL("#bf0000");

        if (sr == bsr)
            itemsArray[index].setColorSR("#568b56");
        else if (sr > bsr)
            itemsArray[index].setColorSR("#bf0000");
        else
            itemsArray[index].setColorSR("#439b20");

        if (fc == bfc)
            itemsArray[index].setColorFC("#568b56");
        else if (fc > bfc)
            itemsArray[index].setColorFC("#bf0000");
        else
            itemsArray[index].setColorFC("#439b20");

        if (sa == bsa)
            itemsArray[index].setColorSA("#568b56");
        else if (sa > bsa)
            itemsArray[index].setColorSA("#bf0000");
        else
            itemsArray[index].setColorSA("#439b20");
    }
}

function createItem(name, internalName, profession, ce, pr, cl, hp, hpMax, st, sl, sr, sa, fc, bce, bpr, bcl, bhpMax, bsl, bsr, bsa, bfc) {
    if (actualAmountOfItems < itemsArray.length)
    {
        var y00 = yAtTop;//not binded for sure
        itemsArray[actualAmountOfItems] = listDelegate.createObject(rootMercenariesList,
                                                {"x": 0,
                                                "y": actualAmountOfItems * heightOfElement + y00,
                                                "width": width, "height": heightOfElement});
        setItem(actualAmountOfItems, name, internalName, profession, ce, pr, cl, hp, hpMax, st, sl, sr, sa, fc, bce, bpr, bcl, bhpMax, bsl, bsr, bsa, bfc);
        ++actualAmountOfItems;
    }
}

function getClickedItemName(y) {
    var h = heightOfElement;
    var y0 = 0;
    var y1 = h;
    y -= yAtTop;
    for (var i=0;i<actualAmountOfItems;++i)
    {
        if (y >= y0 && y <= y1)
            return itemsArray[i].getName();
        y0 += h;
        y1 += h;
    }
    return "nothing";
}

function getClickedItemArt(y) {
    var h = heightOfElement;
    var y0 = 0;
    var y1 = h;
    y -= yAtTop;
    for (var i=0;i<actualAmountOfItems;++i)
    {
        if (y >= y0 && y <= y1)
            return itemsArray[i].getArtSource();
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
