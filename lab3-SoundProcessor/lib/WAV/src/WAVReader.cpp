#include "WAVReader.hpp"

#include "WAVExceptions.hpp"

WAVReader::WAVReader(std::string filePath)
{
    open(std::move(filePath));
}

void WAVReader::open(std::string filePath)
{
    if (filePath.find(".wav") == std::string::npos)
    {
        // WAV exception about not format file
        throw WAVExceptions::BadFileFormat(filePath);
    }
    inputFilePath_ = std::move(filePath);

    inputFile_.open(inputFilePath_, std::ios_base::binary);
    if (!inputFile_.good())
    {
        // WAV exception about bad file opening
        throw WAVExceptions::BadFileOpening(inputFilePath_);
    }

    readHeader();
}

void WAVReader::readHeader()
{
    WAVHeader::Chunk riffChunk;

    inputFile_.read((char *) &riffChunk, sizeof(riffChunk));

    if (!inputFile_.good() || riffChunk.chunkID != WAVSupportedFormat::RIFF)
    {
        // WAV exception about bad riffChunk format
        throw WAVExceptions::BadChunkHeaderFormat(inputFilePath_, WAVSupportedFormat::RIFF);
    }

    WAVHeader::format format;

    inputFile_.read((char *) &format, sizeof(format));

    if (!inputFile_.good() || format != WAVSupportedFormat::WAVE)
    {
        // WAV exception aboud bad format sym
        throw WAVExceptions::BadFormatHeader(inputFilePath_);
    }

    WAVHeader::Chunk fmtChunk;

    inputFile_.read((char *) &fmtChunk, sizeof(fmtChunk));

    if (!inputFile_.good() || fmtChunk.chunkID != WAVSupportedFormat::FMT_)
    {
        throw WAVExceptions::BadChunkHeaderFormat(inputFilePath_,WAVSupportedFormat::FMT_);
    }

    WAVHeader::FMTChunkData fmtData {};

    inputFile_.read((char *) &fmtData, sizeof(fmtData));

    if (!inputFile_.good())
    {
        throw WAVExceptions::BadReadingFile(inputFilePath_);
    }

    if (fmtData.audioFormat != WAVSupportedFormat::AUDIO_FORMAT_PCM ||

        fmtData.numChannels != WAVSupportedFormat::NUM_CHANNELS ||

        fmtData.sampleRate != WAVSupportedFormat::SAMPLE_RATE)
    {
        // WAV excetpion about bad FMT data format
        throw WAVExceptions::BadFMTChunkDataFormat(inputFilePath_);
    }

    WAVHeader::Chunk dataChunk;

    inputFile_.read((char *) &dataChunk, sizeof(dataChunk));

    while (dataChunk.chunkID != WAVSupportedFormat::DATA)
    {
        if (!inputFile_.good())
        {
            throw WAVExceptions::BadReadingFile(inputFilePath_);
        }

        inputFile_.ignore(dataChunk.chunkSize);
        inputFile_.read((char *) &dataChunk, sizeof(dataChunk));
    }
}

bool WAVReader::readSample(SampleBuffer &sampleBuffer)
{
    inputFile_.read((char *) &sampleBuffer, sizeof(Sample) * sampleBuffer.size());

    if (inputFile_.gcount() == 0)
    {
        sampleBuffer.fill(0);
    }

    return inputFile_.gcount();
}