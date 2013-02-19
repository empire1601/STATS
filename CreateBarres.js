var component;
 var sprite;

 function finishCreation() {
     if (component.status == Component.Ready) {
         sprite = component.createObject(appWindow, {"x": 100, "y": 100});
         if (sprite == null) {
             // Error Handling
             console.log("Error creating object");
         }
     } else if (component.status == Component.Error) {
         // Error Handling
         console.log("Error loading component:", component.errorString());
     }
 }
function createSpriteObjects(tx, ty) {
     component = Qt.createComponent("Barre.qml");
     sprite = component.createObject(appWindow, {"x": tx, "y": ty});
    console.log("Crea d'un rect  : " + tx + " : " +ty);

     if (sprite == null) {
         // Error Handling
         console.log("Error creating object");
     }
 }
