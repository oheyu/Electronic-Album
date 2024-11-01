import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0


Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Text {
        id: text
        width: 640
        height: 50
        font.weight:  Font.Black
        text: qsTr("Hello World!")
    }

    Button {
        id: button
        text: qsTr("Print")
        font.weight:  Font.Black
        anchors.fill: parent
        anchors.margins: 10
        onClicked: {
            //可以通过window的data数组访问其子元素
            console.log("window.Text text is : " + window.data[0].text)
            console.log("window.Button text is : " + window.data[1].text)
            //也可以通过id直接访问qml中的元素
            if(text.text == "Hello World"){
                text.text = "Hello Zack"
            }else{
                text.text = "Hello World"
            }
        }
    }
}
