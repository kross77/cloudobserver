using ProtoBuf;

namespace Transport.Protocol
{
    [ProtoContract]
    internal class OperationPongRequest : OperationRequest<OperationResponse> { }
}