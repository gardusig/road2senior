from google.protobuf import timestamp_pb2 as _timestamp_pb2
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class IsTransactionValidRequest(_message.Message):
    __slots__ = ["transactionId", "merchantId", "userId", "cardNumber", "transactionDate", "transactionAmount", "deviceId", "hasCbk"]
    TRANSACTIONID_FIELD_NUMBER: _ClassVar[int]
    MERCHANTID_FIELD_NUMBER: _ClassVar[int]
    USERID_FIELD_NUMBER: _ClassVar[int]
    CARDNUMBER_FIELD_NUMBER: _ClassVar[int]
    TRANSACTIONDATE_FIELD_NUMBER: _ClassVar[int]
    TRANSACTIONAMOUNT_FIELD_NUMBER: _ClassVar[int]
    DEVICEID_FIELD_NUMBER: _ClassVar[int]
    HASCBK_FIELD_NUMBER: _ClassVar[int]
    transactionId: str
    merchantId: str
    userId: str
    cardNumber: str
    transactionDate: _timestamp_pb2.Timestamp
    transactionAmount: float
    deviceId: str
    hasCbk: bool
    def __init__(self, transactionId: _Optional[str] = ..., merchantId: _Optional[str] = ..., userId: _Optional[str] = ..., cardNumber: _Optional[str] = ..., transactionDate: _Optional[_Union[_timestamp_pb2.Timestamp, _Mapping]] = ..., transactionAmount: _Optional[float] = ..., deviceId: _Optional[str] = ..., hasCbk: bool = ...) -> None: ...

class IsTransactionValidResponse(_message.Message):
    __slots__ = ["transactionId", "isValid"]
    TRANSACTIONID_FIELD_NUMBER: _ClassVar[int]
    ISVALID_FIELD_NUMBER: _ClassVar[int]
    transactionId: str
    isValid: bool
    def __init__(self, transactionId: _Optional[str] = ..., isValid: bool = ...) -> None: ...
