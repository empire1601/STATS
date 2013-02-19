import QtQuick 1.0

Rectangle {
    id: appWindow
    property string frameColor: "black"
    property string m_Titre: "Histogramme"
    width: 300; height: 300

    Barre{
        xpos : 20
        freq: 0.8
        nom_Mod : "Modalité1"
    }
    Barre{
        xpos : 40
        freq: 0.4
        nom_Mod : "Modalité2"
    }

    Text {
        anchors { bottom: parent.bottom; horizontalCenter: parent.horizontalCenter; bottomMargin: 20 }
        text: m_Titre
    }
}
