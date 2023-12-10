#pragma once


// Deferred inline implementations.
#include ".global/functions.inl"

#include ".global/logging/LogMessage.inl"
#include ".global/logging/internal/MessageFormat.inl"
#include ".global/logging/internal/MessageChannel.inl"
#include ".global/logging/internal/MessageLocation.inl"
#include ".global/logging/internal/BufferEncoder.inl"

#include ".global/types/RingBuffer.inl"
#include ".global/types/PlainVector.operations.inl"
#include ".global/types/internal/BasicPlainVector.inl"
#include ".global/types/PlainView.operations.inl"
#include ".global/types/internal/BasicPlainView.inl"

#include ".global/algorithms/chars.inl"
#include ".global/algorithms/bytes.inl"

#include ".bootstrap/constants.converting.inl"
