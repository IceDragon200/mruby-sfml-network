MRuby::Gem::Specification.new('mruby-sfml-network') do |spec|
  spec.license = 'MIT'
  spec.authors = ['Corey Powell']
  spec.version = '2.4.0.0'
  spec.summary = 'SFML Network binding'
  spec.description = 'SFML Network binding'
  spec.homepage = 'https://github.com/IceDragon200/mruby-sfml-network'

  spec.add_dependency 'mruby-sfml-system', github: 'IceDragon200/mruby-sfml-system'
  spec.cxx.flags << '-fpermissive'
end
