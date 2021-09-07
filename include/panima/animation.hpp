/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021 Silverlan
 */

#ifndef __PANIMA_ANIMATION_HPP__
#define __PANIMA_ANIMATION_HPP__

#include <cinttypes>
#include <memory>
#include <vector>
#include <string>
#include <mathutil/umath.h>

namespace udm {struct AssetData; enum class Type : uint8_t; struct LinkedPropertyWrapper;};
namespace util {class Path;};
namespace panima
{
	struct Channel;
	class Animation
		: public std::enable_shared_from_this<Animation>
	{
	public:
		enum class Flags : uint32_t
		{
			None = 0u,
			LoopBit = 1u
		};
		Animation()=default;
		void AddChannel(Channel &channel);
		Channel *AddChannel(const util::Path &path,udm::Type valueType);
		const std::vector<std::shared_ptr<Channel>> &GetChannels() const {return const_cast<Animation*>(this)->GetChannels();}
		std::vector<std::shared_ptr<Channel>> &GetChannels() {return m_channels;}
		uint32_t GetChannelCount() const {return m_channels.size();}

		bool Save(udm::LinkedPropertyWrapper &prop) const;
		bool Load(udm::LinkedPropertyWrapper &prop);

		Channel *FindChannel(const util::Path &path);
		const Channel *FindChannel(const util::Path &path) const {return const_cast<Animation*>(this)->FindChannel(path);}

		float GetAnimationSpeedFactor() const {return m_speedFactor;}
		void SetAnimationSpeedFactor(float f) {m_speedFactor = f;}

		void SetName(std::string name) {m_name = std::move(name);}
		const std::string &GetName() const {return m_name;}

		Flags GetFlags() const {return m_flags;}
		bool HasFlags(Flags flags) const {return umath::is_flag_set(m_flags,flags);}

		float GetDuration() const {return m_duration;}
		void SetDuration(float duration) {m_duration = duration;}

		bool operator==(const Animation &other) const {return this == &other;}
		bool operator!=(const Animation &other) const {return !operator==(other);}
	private:
		std::vector<std::shared_ptr<Channel>> m_channels;
		std::string m_name;
		float m_speedFactor = 1.f;
		float m_duration = 0.f;
		Flags m_flags = Flags::None;
	};
};

REGISTER_BASIC_BITWISE_OPERATORS(panima::Animation::Flags)

std::ostream &operator<<(std::ostream &out,const panima::Animation &o);

#endif
