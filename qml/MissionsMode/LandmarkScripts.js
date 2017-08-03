var landmark;
var itemsArray;
var actualAmountOfItems = 0;

function setupList(amountOfItems)
{
    landmark = Qt.createComponent("qrc:/qml/MissionsMode/Landmark.qml");
    if (landmark == null) {
        console.log("Error creating object");
    }
    itemsArray = new Array(amountOfItems);
}

function setItem(index, name, internalName, description) {
    itemsArray[index].setArtSource("qrc:/graphics/Missions/Lands/"+internalName+".png");
    itemsArray[index].setName(name);
    itemsArray[index].setDescription(description);
}

function createItem(x, y, size/*w,h*/, name, internalName, description) {
    if (actualAmountOfItems < itemsArray.length)
    {
        itemsArray[actualAmountOfItems] = landmark.createObject(landmarksManagerIconsHandler,
                                                {"x": x,
                                                "y": y,
                                                "width": size, "height": size});
        setItem(actualAmountOfItems,name,internalName,description);
        itemsArray[actualAmountOfItems].iconClicked.connect(landmarksManager.handleIconClick)
        ++actualAmountOfItems;
    }
}
