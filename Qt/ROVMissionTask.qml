import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2


CheckBox {
    x: 10
    id: checkTask

    style: CheckBoxStyle {
        label: Text {
            id: taskLabel
            color: "white"
            text: checkTask.text
            font.bold: true
        }
    }

}
