// The MIT License (MIT)
//
// Copyright (c) 2015-2017 Simon Ninon <simon.ninon@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <cpp_redis/builders/builder_iface.hpp>
#include <cpp_redis/builders/integer_builder.hpp>
#include <cpp_redis/core/reply.hpp>

namespace cpp_redis {

namespace builders {

//!
//! builder to build redis bulk string replies
//!
class bulk_string_builder : public builder_iface {
public:
  //! ctor
  bulk_string_builder(void);
  //! dtor
  ~bulk_string_builder(void) = default;

  //! copy ctor
  bulk_string_builder(const bulk_string_builder&) = delete;
  //! assignment operator
  bulk_string_builder& operator=(const bulk_string_builder&) = delete;

public:
  //!
  //! take data as parameter which is consumed to build the reply
  //! every bytes used to build the reply must be removed from the buffer passed as parameter
  //!
  //! \param data data to be consumed
  //! \return current instance
  //!
  builder_iface& operator<<(std::string& data);

  //!
  //! \return whether the reply could be built
  //!
  bool reply_ready(void) const;

  //!
  //! \return reply object
  //!
  reply get_reply(void) const;

  //!
  //! \return the parsed bulk string
  //!
  const std::string& get_bulk_string(void) const;

  //!
  //! \return whether the bulk string is null
  //!
  bool is_null(void) const;

private:
  void build_reply(void);
  bool fetch_size(std::string& str);
  void fetch_str(std::string& str);

private:
  //!
  //! builder used to get bulk string size
  //!
  integer_builder m_int_builder;

  //!
  //! bulk string size
  //!
  int m_str_size;

  //!
  //! bulk string
  //!
  std::string m_str;

  //!
  //! whether the bulk string is null
  //!
  bool m_is_null;

  //!
  //! whether the reply is ready or not
  //!
  bool m_reply_ready;

  //!
  //! reply to be built
  //!
  reply m_reply;
};

} // namespace builders

} // namespace cpp_redis
