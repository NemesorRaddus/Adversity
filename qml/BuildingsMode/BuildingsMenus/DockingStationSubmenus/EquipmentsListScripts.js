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
    listDelegate = Qt.createComponent("qrc:/qml/BuildingsMode/BuildingsMenus/DockingStationSubmenus/EquipmentsListDelegate.qml");
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

function setItem(index, name, internalName, type, tier, cost, bn, bv) {
    itemsArray[index].setArtSource("qrc:/graphics/Equipment/"+GlobalsCpp.alterNormalTextToInternal(type)+"/Tier_"+tier+'/'+internalName+".png");
    itemsArray[index].setName(name);
    itemsArray[index].setType(type);
    itemsArray[index].setTier(tier);
    itemsArray[index].setCost(cost);
    itemsArray[index].setBonus(0,bn[0],bv[0]);
    itemsArray[index].setBonus(1,bn[1],bv[1]);
    itemsArray[index].setBonus(2,bn[2],bv[2]);
    itemsArray[index].setBonus(3,bn[3],bv[3]);
    itemsArray[index].setBonus(4,bn[4],bv[4]);
    itemsArray[index].setBonus(5,bn[5],bv[5]);
}

function createItem(name, internalName, type, tier, cost, bn, bv) {
    if (actualAmountOfItems < itemsArray.length)
    {
        var y00 = yAtTop;//not binded for sure
        itemsArray[actualAmountOfItems] = listDelegate.createObject(rootEquipmentsList,
                                                {"x": 0,
                                                "y": actualAmountOfItems * heightOfElement + y00,
                                                "width": width, "height": heightOfElement});
        setItem(actualAmountOfItems, name, internalName, type, tier, cost, bn, bv);
        ++actualAmountOfItems;
    }
}

function getClickedItemIndex(x,y) {
    var h = heightOfElement;
    var y0 = 96;
    var y1 = y0 + 79;
    y -= yAtTop;
    for (var i=0;i<actualAmountOfItems;++i)
    {
        if (y >= y0 && y <= y1 && x >= 900 && x <= 1030)
            return i;
        y0 += h;
        y1 += h;
    }
    return -1;
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
