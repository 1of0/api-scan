#pragma once

#include "SourceScanner.h"
#include "Translator.h"
#include "JsonFormatter.h"
#include "XmlFormatter.h"

#include "tclap/CmdLine.h"

using std::string;
using std::vector;

using ApiScan::SourceScanner;
using ApiScan::FunctionInfo;
using ApiScan::ParameterInfo;
using ApiScan::Translator;
using ApiScan::Formatter;
using ApiScan::XmlFormatter;
using ApiScan::JsonFormatter;

using TCLAP::CmdLine;
using TCLAP::UnlabeledMultiArg;
