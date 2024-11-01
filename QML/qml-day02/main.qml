import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Rectangle")

    Rectangle{
        id: rect1
        color: "red"
        width: 100
        height: 100
        radius: 20
        antialiasing: true;
        gradient: Gradient{
            GradientStop{ position: 0.0; color: "red"}
            GradientStop { position: 0.33; color: "yellow" }
            GradientStop { position: 1.0; color: "blue" }

        }

        anchors.alignWhenCentered: false
        anchors.centerIn : parent

        anchors.verticalCenterOffset: -parent.height/3
    }

    Rectangle{
        id: rect2
        color: "red"
        width: 100
        height: 100
        radius: 20
        antialiasing: true;
        gradient: Gradient{
            GradientStop{ position: 0.0; color: "red"}
            GradientStop { position: 0.33; color: "yellow" }
            GradientStop { position: 1.0; color: "blue" }

        }

        anchors.alignWhenCentered: false
        anchors.centerIn : parent
    }

    Rectangle{
        id: rect3
        color: "red"
        width: 100
        height: 100
        radius: 20
        antialiasing: true;
        gradient: Gradient{
            GradientStop{ position: 0.0; color: "red"}
            GradientStop { position: 0.33; color: "yellow" }
            GradientStop { position: 1.0; color: "blue" }

        }

        anchors.alignWhenCentered: false
        anchors.centerIn : parent

        anchors.verticalCenterOffset: parent.height/3
    }
}
