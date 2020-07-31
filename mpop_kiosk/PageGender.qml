import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

/**
 * Page that contains the widget to select my gender.
 */
RowLayout {
    id: thisPage

    signal nextButtonClicked()
    signal previousButtonClicked()

    Label {
        Layout.alignment: Qt.AlignCenter
        text: qsTr("You are...")
        font.pixelSize: 36
    }

    ListView {
        Layout.margins: 0
        Layout.fillWidth: false
        Layout.fillHeight: true
        orientation: Qt.Vertical
        width: currentItem.width
        model: ModelGenders {
            id: modelGenders
        }

        delegate: WidgetChoiceButton {
            text: name_fr // Property of items in the model.
            height: parent.height / parent.count
            spacing: 0
        }
    }

    WidgetPreviousNext {
        onNextButtonClicked: thisPage.nextButtonClicked()
        onPreviousButtonClicked: thisPage.previoiusButtonClicked()
    }
}