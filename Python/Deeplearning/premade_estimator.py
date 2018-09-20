#  Copyright 2016 The TensorFlow Authors. All Rights Reserved.
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
"""An Example of a DNNClassifier for the Iris dataset."""
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
import tensorflow as tf

import samples.core.get_started.iris_data as iris_data

parser = argparse.ArgumentParser()
parser.add_argument('--batch_size', default=250, type=int, help='batch size')
parser.add_argument('--train_steps', default=2500, type=int,
                    help='number of training steps')

def main(argv):
    args = parser.parse_args(argv[1:])
    #Fetch the data
    (train_x, train_y), (test_x, test_y) = iris_data.load_data()

    # Feature columns describe how to use the input.
    my_feature_columns = [
        tf.feature_column.numeric_column(key='x1'),
        tf.feature_column.numeric_column(key='x2'),
        tf.feature_column.numeric_column(key='x3'),
        tf.feature_column.numeric_column(key='x4'),
        tf.feature_column.numeric_column(key='x5')
    ]

    classifier = tf.estimator.DNNClassifier(
        feature_columns=my_feature_columns,
        # Two hidden layers of 10 nodes each.
        hidden_units=[10, 30, 10],
        # The model must choose between 5 classes.
        n_classes=5)

    # Train the Model.
    classifier.train(
        input_fn=lambda: iris_data.train_input_fn(train_x, train_y,
                                                  args.batch_size),
        steps=args.train_steps)

    # Evaluate the model.
    eval_result = classifier.evaluate(
        input_fn=lambda: iris_data.eval_input_fn(test_x, test_y,
                                                 args.batch_size))

    print('\nTest set accuracy: {accuracy:0.3f}\n'.format(**eval_result))

if __name__ == '__main__':
    tf.logging.set_verbosity(tf.logging.INFO)
    tf.app.run(main)