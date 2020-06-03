## QR-Code Design

Can be divided into 3 parts:

1. fixed patterns
2. format information
3. message

### Fixed patterns

* Position elements: 8x8-bit squares placed in the top-left, top-right, bottom-left corners

* Alignment elements: 5x5-bit squares placed as patterns over the qr-symbol

* 0-1-0-1... Lines with a width of 1 that connect the position elements

* Single 0-bit at the top-right of the bottom-left position element

### Format Information

* Contains the error correction level and the mask pattern

* Placed underneath, and to the right of the position elements

### Message

Format: [ encoding mode ] [ message length ] [ message ] [ filler elements ] [ end of message (0b0000) ] [ error correction elements ]

* encoding mode: the type of message to be encoded
* message length: the length of the message to be encoded
* filler elements: if the message does not fill the entire message capacity, fill the rest of the message with filler elements
* end of message: signal the end of the message
* error correction elements: elements for error correction